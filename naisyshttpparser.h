#ifndef NAISYS_NAISYSHTTPPARSER_H
#define NAISYS_NAISYSHTTPPARSER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

#include "naisysdefs.h"
#include "naisysmethodhandler.h"

namespace NaiSys {

class NaiSysHttpParser : public QObject
{
    Q_OBJECT
public:
    explicit NaiSysHttpParser(QObject *parent = nullptr);
    NaiSysHttpParser(QTcpSocket *socket, QObject *parent = nullptr);
    QByteArray renderHttp() const;

    DesirializedData desirialized() const;
    void setDesirialized(const DesirializedData &newDesirialized);

signals:

private:
    QTcpSocket* m_socket;
    DesirializedData m_desirialized;

};

} // namespace NaiSys

#endif // NAISYS_NAISYSHTTPPARSER_H
