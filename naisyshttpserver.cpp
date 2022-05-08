#include "naisyshttpserver.h"

namespace NaiSys {
NaiSysHttpServer::NaiSysHttpServer(QObject *parent)
    : QTcpServer{parent}
{

}

NaiSysHttpServer::NaiSysHttpServer(const ServerAddress &lAddr, QObject *parent)
    : QTcpServer{parent},
      m_listenPort{lAddr._listen_port},
      m_listenAddress{lAddr._listen_address}
{

}

bool NaiSysHttpServer::startServer()
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

void NaiSysHttpServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Opening socket";
    NaiSys::ConnectionThread *workerThread = new NaiSys::ConnectionThread(socketDescriptor, this);
    workerThread->setListenPort(m_listenPort);
    workerThread->setListenAddress(m_listenAddress);
    connect(workerThread, SIGNAL(finished()), workerThread,SLOT(deleteLater()), Qt::DirectConnection);
    workerThread->start();
}

int NaiSysHttpServer::listenPort() const
{return m_listenPort;}

void NaiSysHttpServer::setListenPort(int newListenPort)
{m_listenPort = newListenPort;}

const QString &NaiSysHttpServer::listenAddress() const
{return m_listenAddress;}

void NaiSysHttpServer::setListenAddress(const QString &newListenAddress)
{m_listenAddress = newListenAddress;}
}
