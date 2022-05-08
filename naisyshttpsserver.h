#ifndef NAISYS_NAISYSHTTPSSERVER_H
#define NAISYS_NAISYSHTTPSSERVER_H

#define nErrorLog "[SERVER_ERROR_MSG]: "
#define nMsgLog "[SERVER_BASIC_MSG]: "

#include <QTcpServer>
#include <QObject>
#include <QSslSocket>

#include "naisysdefs.h"
#include "sslconnectionthread.h"

namespace NaiSys {

class NaiSysHttpsServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit NaiSysHttpsServer(QObject *parent = nullptr);
    NaiSysHttpsServer(const ServerAddress& lAddr = *new ServerAddress, QObject *parent = nullptr);
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

} // namespace NaiSys

#endif // NAISYS_NAISYSHTTPSSERVER_H
