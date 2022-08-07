#ifndef NAISYS_NaiSysHttpRequest_H
#define NAISYS_NaiSysHttpRequest_H

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
    NaiSysHttpRequest();
    explicit NaiSysHttpRequest(const QByteArray &data);
    NaiSysHttpRequest(const QByteArray &header, const QByteArray &body);

    void appendDefinedHeader(const int eHeader, const QByteArray &value);
    void appendRawHeader(const QByteArray &key, const QByteArray &value);

    const QByteArray &header() const;
    void setHeader(const QByteArray &newHeader);
    const QByteArray &body() const;
    void setBody(const QByteArray &newBody);

    void appendToBody(const QByteArray &data);

private:
    QByteArray m_header, m_body;
};

} // namespace NaiSys

#endif // NAISYS_NaiSysHttpRequest_H
