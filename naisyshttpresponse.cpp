#include "naisyshttpresponse.h"

namespace NaiSys {

NaiSysHttpResponse::NaiSysHttpResponse()
{
    m_httpHeader.append(__init_header__);
}

const QByteArray &NaiSysHttpResponse::toByteArray() const
{
    return *new QByteArray(m_httpHeader+"\r\n"+m_httpBody);
}

void NaiSysHttpResponse::setRawHeader(const QByteArray &key, const QByteArray &value)
{
    m_httpHeader.append(key+": "+value+"\r\n");
}

const QByteArray &NaiSysHttpResponse::httpHeader() const
{return m_httpHeader;}

void NaiSysHttpResponse::setHttpHeader(const QByteArray &newHttpHeader)
{m_httpHeader = newHttpHeader;}

const QByteArray &NaiSysHttpResponse::httpBody() const
{return m_httpBody;}

void NaiSysHttpResponse::setHttpBody(const QByteArray &newHttpBody)
{m_httpBody = newHttpBody;}

}
