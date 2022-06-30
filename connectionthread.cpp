#include "connectionthread.h"

namespace NaiSys {
ConnectionThread::ConnectionThread(const qintptr descriptor,QObject *parent)
    : QThread{parent},
      m_descriptor{descriptor},
      m_expectingBody{0}
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
#if QT_VERSION >= 0x06000
    QObject::connect(&m_tcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
#else
    QObject::connect(&m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
#endif

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
    auto const _b = m_tcpSocket->readAll();

    qDebug() << "{{INPUT}} $$__ "<< _b;

    auto reqst = NaiSysHttpRequest(_b);

    if(m_expectingBody){
        reqst = m_bufferRequest;
        reqst.setBody(_b);
        m_expectingBody = false;
    }

    auto parser = HttpParser(reqst);

    auto const _size = (qsizetype)parser.desirialized()._header.value("Content-Length").toString().toInt()
            - parser.desirialized()._body.size();
    qDebug() << "////___ BYTES MISSING: "<< _size;

    if(_size){
        this->m_expectingBody = true;
        qDebug() << "{{AWAITING SOME DATA}}: " << _size;
        m_bufferRequest = reqst;
        m_tcpSocket->flush();
        auto resp = parser.getDefaultResponse();
        m_tcpSocket->write(resp.toByteArray());
        return;
    }

    m_tcpSocket->flush();
    auto resp = parser.renderHttp();
    m_tcpSocket->write(resp.toByteArray());

    if(!parser.keepAlive())
    {
        qDebug() << "Attempting disconnect";
    }
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
