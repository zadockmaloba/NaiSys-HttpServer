#include "naisyshttpsserver.h"

namespace NaiSys {

NaiSysHttpsServer::NaiSysHttpsServer(QObject *parent)
    : QTcpServer{parent}
{

}

NaiSysHttpsServer::NaiSysHttpsServer(const ServerAddress &lAddr, QObject *parent)
    : QTcpServer{parent},
      m_listenPort{lAddr._listen_port},
      m_listenAddress{lAddr._listen_address}
{

}

bool NaiSysHttpsServer::startServer()
{
    if(!this->listen(QHostAddress(m_listenAddress), m_listenPort)){
        qDebug() << nErrorLog"Server Failed To Start.";
        return false;
    }
    else {
        qDebug() << nMsgLog"Server Started Succesfully";
        qDebug() << nMsgLog"Listening on [Addr]: "
                 <<m_listenAddress
                 <<" [Port]: "<<QString::number(m_listenPort);
    }
    return true;
}

void NaiSysHttpsServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << nMsgLog"Opening socket";
    sslConnectionThread *workerThread = new sslConnectionThread(socketDescriptor, this);
    workerThread->setListenPort(m_listenPort);
    workerThread->setListenAddress(m_listenAddress);

    workerThread->setSslObject(this->m_sslObj);

    QObject::connect(workerThread, SIGNAL(finished()), workerThread,SLOT(deleteLater()), Qt::DirectConnection);
    workerThread->start();
}

const NaiSys::SslObject &NaiSysHttpsServer::sslObj() const
{
    return m_sslObj;
}

void NaiSysHttpsServer::setSslObj(const NaiSys::SslObject &newSslObj)
{
    m_sslObj = newSslObj;
}

int NaiSysHttpsServer::listenPort() const
{return m_listenPort;}

void NaiSysHttpsServer::setListenPort(int newListenPort)
{m_listenPort = newListenPort;}

const QString &NaiSysHttpsServer::listenAddress() const
{return m_listenAddress;}

void NaiSysHttpsServer::setListenAddress(const QString &newListenAddress)
{m_listenAddress = newListenAddress;}

} // namespace NaiSys
