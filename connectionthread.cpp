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
    //QObject::connect(m_tcpSocket, &QTcpSocket::errorOccurred, this, &ConnectionThread::onErrorOccurred);
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
    auto const _b = m_tcpSocket->readAll();
    m_tcpSocket->flush();
    NaiSysHttpRequest _req(_b);
    NaiSysHttpParser _parse;
    _parse.setDesirialized(*_req.getDesirialized());
    auto const _a = _parse.renderHttp();

    QFile m_file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/HttpServer/test.html");

    NaiSysHttpResponse _resp;
    _resp.setHttpBody(_a);
    _resp.setRawHeader("Connection", "keep-alive");
    _resp.setRawHeader("Content-Length", QByteArray::number(_a.size()));
    m_tcpSocket->write(_resp.toByteArray());
}

void ConnectionThread::onConnected()
{
    qDebug()<<"Connection Established";
}

void ConnectionThread::onDisconnected()
{
    m_tcpSocket->close();
    m_tcpSocket->deleteLater();
    qDebug() << "Socket Closed Successfully";
    this->exit(0);
}

void ConnectionThread::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
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