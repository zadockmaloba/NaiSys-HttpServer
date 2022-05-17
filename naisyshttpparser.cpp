#include "naisyshttpparser.h"

namespace NaiSys {

HttpParser::HttpParser()
{

}

HttpParser::HttpParser(const NaiSysHttpRequest &request)
{
    this->m_desirialized = { HttpParser::getJsonHeader(request.header()),
                             request.body(),
                             request.header()
                           };
}

HttpParser::HttpParser(const NaiSysHttpResponse &response)
{
    this->m_desirialized = { HttpParser::getJsonHeader(response.header()),
                             response.body(),
                             response.header()
                           };
}

const NaiSysHttpResponse HttpParser::renderHttp()
{
    qDebug() << "[HTTPPARSER]" << " __// "<< m_desirialized._body;
    if(m_desirialized._header.value("Method").toString() == "POST"){
        qDebug() << "POST METHOD";
        return NaiSys::MethodHandler(m_desirialized).post();
    }
    else if(m_desirialized._header.value("Method").toString() == "GET"){
        qDebug() << "GET METHOD";
        return NaiSys::MethodHandler(m_desirialized).get();
    }
    return NaiSys::MethodHandler().defaultResponse();
}

const DesirializedData &HttpParser::desirialized() const
{return m_desirialized;}

void HttpParser::setDesirialized(const DesirializedData &newDesirialized)
{m_desirialized = newDesirialized;}

const DesirializedData HttpParser::getDesirializedData([[maybe_unused]]QByteArray &data)
{
    return DesirializedData(); //TODO: implement
}

const QJsonObject HttpParser::getJsonHeader(const QByteArray &header)
{
    QJsonObject jsObj;
    auto const _b = QString::fromUtf8(header).split("\r\n");
    auto const _d = _b[0].split(" ");
    if(_d.size() >= 3){
        jsObj = {{"Method", _d[0]},
                 {"Path", _d[1]},
                 {"Protocol", _d[2]}};

        for(int i=0; i<_b.size()-1; ++i){
            auto const _c = _b[i+1].split(":");
            jsObj.insert(_c[0], QJsonValue(_c[1]));
        }
    }
    return jsObj;
}

} // namespace NaiSys
