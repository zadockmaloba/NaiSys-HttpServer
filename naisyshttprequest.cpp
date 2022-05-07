#include "naisyshttprequest.h"

namespace NaiSys {

NaiSysHttpRequest::NaiSysHttpRequest(const QByteArray &data)
{
    QJsonObject jsObj;
    auto const _a = QString::fromUtf8(data).split("\r\n\r\n");
    this->m_rawHeader = _a[0].toUtf8(); this->m_rawBody = _a[1].toUtf8();
    auto const _b = _a[0].split("\r\n");
    {
        auto const _d = _b[0].split(" ");
        Q_ASSERT(_d.size() == 3);
        jsObj.insert("Method", _d[0]);
        jsObj.insert("Path", _d[1]);
        jsObj.insert("Protocol", _d[2]);
    }
    for(int i=0; i<_b.size()-1; ++i){
        auto const _c = _b[i+1].split(":");
        jsObj.insert(_c[0], QJsonValue(_c[1]));
    }
    m_headerJson = jsObj;
    qDebug() << m_headerJson;
}

const DesirializedData *NaiSysHttpRequest::getDesirialized() const
{
    return new DesirializedData{m_headerJson, m_rawBody};
}

const QByteArray &NaiSysHttpRequest::rawHeader() const
{return m_rawHeader;}

const QByteArray &NaiSysHttpRequest::rawBody() const
{return m_rawBody;}

const QJsonObject &NaiSysHttpRequest::headerJson() const
{return m_headerJson;}

} // namespace NaiSys
