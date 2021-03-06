#include "sslconnectionthread.h"
#include "QtGlobal"

namespace NaiSys {

sslConnectionThread::sslConnectionThread(const qintptr descriptor, QObject *parent)
    : QThread{parent},
      m_descriptor{descriptor},
      m_expectingBody{0}
{

}

void sslConnectionThread::run()
{
    QSslSocket m_sslSocket;

    m_sslSocket.setLocalCertificate(m_sslObject.__cert_dir);
    m_sslSocket.setPrivateKey(m_sslObject.__key_dir);

    if(!m_sslSocket.setSocketDescriptor(m_descriptor)){
        qDebug() << (m_sslSocket.errorString());
        return;
    }
    else qDebug() << "Socket created on new Thread : "<< this->currentThread();

    m_sslSocket.startServerEncryption();

    QObject::connect(&m_sslSocket, &QSslSocket::encrypted, this, &sslConnectionThread::ready);
    QObject::connect(&m_sslSocket, &QSslSocket::connected, this, &sslConnectionThread::onConnected);
    QObject::connect(&m_sslSocket, &QIODevice::readyRead, this, &sslConnectionThread::onReadyRead);
    QObject::connect(&m_sslSocket, &QSslSocket::disconnected, this, &sslConnectionThread::onDisconnected);
#if QT_VERSION > QT_VERSION_CHECK(5, 15, 0)
    QObject::connect(&m_sslSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
#else
    QObject::connect(&m_sslSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));
#endif

    exec();
}

const NaiSys::SslObject &sslConnectionThread::sslObject() const
{return m_sslObject;}

void sslConnectionThread::setSslObject(const NaiSys::SslObject &newSslObject)
{m_sslObject = newSslObject;}

qintptr sslConnectionThread::descriptor() const
{return m_descriptor;}

void sslConnectionThread::setDescriptor(qintptr newDescriptor)
{m_descriptor = newDescriptor;}

int sslConnectionThread::listenPort() const
{return m_listenPort;}

void sslConnectionThread::setListenPort(int newListenPort)
{m_listenPort = newListenPort;}

const QString &sslConnectionThread::listenAddress() const
{return m_listenAddress;}

void sslConnectionThread::setListenAddress(const QString &newListenAddress)
{m_listenAddress = newListenAddress;}


void sslConnectionThread::onAboutToClose()
{
    qDebug() << "[sslSOCKET]: Closing socket....";
}

void sslConnectionThread::onBytesWritten(qint64 bytes)
{
    qDebug() << "[BYTES_WRITTEN]: "<<bytes;
}

void sslConnectionThread::onChannelBytesWritten(int channel, qint64 bytes)
{
    qDebug() << "[CHANNEL]: "<<channel<<" [BYTES_WRITTEN]: "<<bytes;
}

void sslConnectionThread::onChannelReadyRead(int channel)
{
    qDebug() << "[CHANNEL]: "<<channel;
}

void sslConnectionThread::onReadChannelFinished()
{
    qDebug() << "[CHANNEL]: Read Channel finnished";
}

void sslConnectionThread::onReadyRead()
{
    auto const m_sslSocket = qobject_cast<QSslSocket*> (sender());
    auto const _b = m_sslSocket->readAll();

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
        m_sslSocket->flush();
        auto resp = parser.getDefaultResponse();
        m_sslSocket->write(resp.toByteArray());
        return;
    }
    auto resp = parser.renderHttp();
    m_sslSocket->flush();
    m_sslSocket->write(resp.toByteArray());

    if(!parser.keepAlive())
    {
        qDebug() << "Attempting disconnect";
    }
}

void sslConnectionThread::onConnected()
{
    qDebug() << "[SOCKET]: Connection established";
}

void sslConnectionThread::onDisconnected()
{
    auto const m_sslSocket = qobject_cast<QSslSocket*> (sender());
    m_sslSocket->close();
    qDebug() << "Socket Closed Successfully";
    this->exit(0);
}

void sslConnectionThread::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    auto const _b = qobject_cast<QSslSocket*> (sender());
    qDebug() << "ERROR: " << _b->errorString() << "PORT: " << _b->localPort();
    qDebug() << socketError;
}

void sslConnectionThread::onHostFound()
{

}

void sslConnectionThread::onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qDebug()<< "PROXY AUTH() REQUIRED: " << proxy << authenticator;
}

void sslConnectionThread::onStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket State: " << socketState;
}

void sslConnectionThread::ready()
{
    qDebug() << "Ready";
}

}
