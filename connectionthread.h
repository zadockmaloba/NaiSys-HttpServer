#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>
#include <QNetworkProxy>
#include <QAuthenticator>
#include <QAbstractSocket>

#include <QFile>
#include <QStandardPaths>
#include <memory>

#include "naisyshttpresponse.h"
#include "naisyshttprequest.h"
#include "naisyshttpparser.h"

namespace NaiSys {
class ConnectionThread : public QThread
{
    Q_OBJECT
public:
    explicit ConnectionThread(const qintptr descriptor, QObject *parent = nullptr);
    void run();
    int listenPort() const;
    void setListenPort(int newListenPort);
    const QString &listenAddress() const;
    void setListenAddress(const QString &newListenAddress);

    QTcpSocket *tcpSocket() const;
    void setTcpSocket(QTcpSocket *newTcpSocket);

private slots:
    //IODevice signals
    void onAboutToClose();
    void onBytesWritten(qint64 bytes);
    void onChannelBytesWritten(int channel, qint64 bytes);
    void onChannelReadyRead(int channel);
    void onReadChannelFinished();
    void onReadyRead();
    //AbstractSocket signals
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);
    void onHostFound();
    void onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void onStateChanged(QAbstractSocket::SocketState socketState);

private:
    //std::unique_ptr<QTcpSocket> m_tcpSocket;
    QTcpSocket *m_tcpSocket;
    qintptr m_descriptor;
    int m_listenPort;
    QString m_listenAddress;
};
}

#endif // CONNECTIONTHREAD_H
