#ifndef NAISYSHTTPSERVER_H
#define NAISYSHTTPSERVER_H

#define nErrorLog "[SERVER_ERROR_MSG]: "
#define nMsgLog "[SERVER_BASIC_MSG]: "

#include <QTcpServer>
#include <QObject>

#include "naisysdefs.h"
#include "connectionthread.h"
#include "systemconfig.h"

namespace NaiSys {

class NaiSysHttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit NaiSysHttpServer(QObject *parent = nullptr);
    NaiSysHttpServer(const ServerAddress& lAddr = *new ServerAddress, QObject *parent = nullptr);
    bool startServer();

    int listenPort() const;
    void setListenPort(int newListenPort);
    const QString &listenAddress() const;
    void setListenAddress(const QString &newListenAddress);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    int m_listenPort;
    QString m_listenAddress;
};
}

#endif // NAISYSHTTPSERVER_H
