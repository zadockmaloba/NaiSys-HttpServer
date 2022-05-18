#include "sslconnectionthread.h"

namespace NaiSys {

sslConnectionThread::sslConnectionThread(const qintptr descriptor, QObject *parent)
    : QThread{parent},
      m_descriptor{descriptor}
{

}

void sslConnectionThread::run()
{
    QSslSocket m_sslSocket;

    m_sslSocket.setLocalCertificate(SystemConfig::readConfigFile().value("Ssl-Cert").toString());
    m_sslSocket.setPrivateKey(SystemConfig::readConfigFile().value("Ssl-Key").toString());

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
    QObject::connect(&m_sslSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(onErrorOccurred(QAbstractSocket::SocketError)));

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
    QByteArray _b;

    while (m_sslSocket->bytesAvailable()) {
        _b.append(m_sslSocket->readLine());
    }
    m_sslSocket->flush();

    auto const reqst = NaiSysHttpRequest(_b);
    auto parser = HttpParser(reqst);

    if(parser.desirialized()._header.value("Content-Lenqth").toInt()
            > parser.desirialized()._body.size()){
        m_sslSocket->waitForBytesWritten();
        qDebug() << "BYTES MISSING: "
                 << parser.desirialized()._header.value("Content-Lenqth").toInt()
                    - parser.desirialized()._body.size();
        while (m_sslSocket->bytesAvailable()) {
            parser.desirialized()._body.append( m_sslSocket->readLine());
        }
    }

    auto resp = parser.renderHttp();
    m_sslSocket->write(resp.toByteArray());
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
