#include "connectionthread.h"

namespace NaiSys {
ConnectionThread::ConnectionThread(const qintptr descriptor,QObject *parent)
    : QThread{parent},
      m_descriptor{descriptor}
{

}

int ConnectionThread::listenPort() const
{return m_listenPort;}

void ConnectionThread::setListenPort(int newListenPort)
{m_listenPort = newListenPort;}

const QString &ConnectionThread::listenAddress() const
{return m_listenAddress;}

void ConnectionThread::setListenAddress(const QString &newListenAddress)
{m_listenAddress = newListenAddress;}

void ConnectionThread::run()
{
    QTcpSocket m_tcpSocket;

    if(!m_tcpSocket.setSocketDescriptor(m_descriptor)){
        qDebug() << (m_tcpSocket.errorString());
        return;
    }
    else qDebug() << "Socket created on new Thread : "<< this->currentThread();

    QObject::connect(&m_tcpSocket, &QTcpSocket::connected, this, &ConnectionThread::onConnected);
    QObject::connect(&m_tcpSocket, &QIODevice::readyRead, this, &ConnectionThread::onReadyRead);
    QObject::connect(&m_tcpSocket, &QTcpSocket::disconnected, this, &ConnectionThread::onDisconnected);
    QObject::connect(&m_tcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
    //QObject::connect(m_tcpSocket, &QTcpSocket::proxyAuthenticationRequired, this, &ConnectionThread::onProxyAuthenticationRequired);
    exec();
}

void ConnectionThread::onAboutToClose()
{

}

void ConnectionThread::onBytesWritten(qint64 bytes)
{
    qDebug() << "Bytes: "<<bytes;
}

void ConnectionThread::onChannelBytesWritten(int channel, qint64 bytes)
{
    qDebug() <<"Channel: "<<channel<<" Bytes: "<<bytes;
}

void ConnectionThread::onChannelReadyRead(int channel)
{
    qDebug() <<"Channel: "<<channel;
}

void ConnectionThread::onReadChannelFinished()
{

}

void ConnectionThread::onReadyRead()
{
    auto const m_tcpSocket = qobject_cast<QTcpSocket*> (sender());
    QByteArray _b;

    while (m_tcpSocket->bytesAvailable()) {
        _b.append(m_tcpSocket->readLine());
    }
    qDebug() << _b;
    m_tcpSocket->flush();

    auto const reqst = NaiSysHttpRequest(_b);

    auto parser = HttpParser(reqst);

    if(parser.desirialized()._header.value("Content-Lenqth").toInt()
            > parser.desirialized()._body.size()){
        m_tcpSocket->waitForBytesWritten();
        qDebug() << "BYTES MISSING: "
                 << parser.desirialized()._header.value("Content-Lenqth").toInt()
                    - parser.desirialized()._body.size();
        while (m_tcpSocket->bytesAvailable()) {
            parser.desirialized()._body.append( m_tcpSocket->readLine());
        }
    }

    auto resp = parser.renderHttp();
    m_tcpSocket->write(resp.toByteArray());
}

void ConnectionThread::onConnected()
{
    qDebug()<<"Connection Established";
}

void ConnectionThread::onDisconnected()
{
    auto const m_tcpSocket = qobject_cast<QTcpSocket*> (sender());
    m_tcpSocket->close();
    qDebug() << "Socket Closed Successfully";
    this->exit(0);
}

void ConnectionThread::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    auto const _b = qobject_cast<QTcpSocket*> (sender());
    qDebug() << "ERROR: " << _b->errorString() << "PORT: " << _b->localPort();
    qDebug() << socketError;
}

void ConnectionThread::onHostFound()
{

}

void ConnectionThread::
onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qDebug()<< "PROXY AUTH() REQUIRED: " << proxy << authenticator;
}

void ConnectionThread::onStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket State: " << socketState;
}
}
