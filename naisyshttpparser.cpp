#include "naisyshttpparser.h"

namespace NaiSys {

NaiSysHttpParser::NaiSysHttpParser(QObject *parent)
    : QObject{parent}
{

}

NaiSysHttpParser::NaiSysHttpParser(QTcpSocket *socket, QObject *parent)
    : QObject{parent},
      m_socket{socket}
{

}

QByteArray NaiSysHttpParser::renderHttp() const //TODO: Avoid copying
{
    auto const jsObj = m_desirialized._header;
    if (jsObj.value("Method").toString() == "GET"){
        qDebug() << "GET Request "<< jsObj.value("Path").toString();
        auto const v = NaiSysMethodHandler().get(jsObj.value("Path").toString());
        return v;
    }
    else if (jsObj.value("Method").toString() == "POST"){
        qDebug() << "POST Request";
        return QByteArray();
    }
    else if (jsObj.value("Method").toString() == "PUT"){
        qDebug() << "PUT Request";
        return QByteArray();
    }
    return QByteArray();
}

DesirializedData NaiSysHttpParser::desirialized() const
{return m_desirialized;}

void NaiSysHttpParser::setDesirialized(const DesirializedData &newDesirialized)
{m_desirialized = newDesirialized;}

} // namespace NaiSys
