#ifndef NAISYS_NAISYSHTTPREQUEST_H
#define NAISYS_NAISYSHTTPREQUEST_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

#include "naisysdefs.h"

namespace NaiSys {

class NaiSysHttpRequest
{
public:
    NaiSysHttpRequest(const QByteArray &data);
    const DesirializedData *getDesirialized() const;

    const QByteArray &rawHeader() const;
    const QByteArray &rawBody() const;
    const QJsonObject &headerJson() const;

private:
    QByteArray m_rawHeader, m_rawBody;
    QJsonObject m_headerJson;
};

} // namespace NaiSys

#endif // NAISYS_NAISYSHTTPREQUEST_H
