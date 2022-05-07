#ifndef NaiSysHttpResponse_H
#define NaiSysHttpResponse_H

#include <QObject>

namespace NaiSys {
class NaiSysHttpResponse
{
public:
    NaiSysHttpResponse();
    const QByteArray &toByteArray() const;
    void setRawHeader(const QByteArray& key, const QByteArray& value);

    const QByteArray &httpHeader() const;
    void setHttpHeader(const QByteArray &newHttpHeader);
    const QByteArray &httpBody() const;
    void setHttpBody(const QByteArray &newHttpBody);

private:
    const QByteArray __init_header__ = "HTTP/1.1 200 Ok\r\n";
    QByteArray m_httpHeader, m_httpBody;
};
}

#endif // NaiSysHttpResponse_H
