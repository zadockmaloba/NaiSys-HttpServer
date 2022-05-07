#include "naisysmethodhandler.h"

namespace NaiSys {

NaiSysMethodHandler::NaiSysMethodHandler(QObject *parent)
    : QObject{parent}
{
}

const QByteArray &NaiSysMethodHandler::get(const QString &path)
{
    qDebug() << path;
    QString _path;
    _path = (m_routingTable[path] != "") ?
                SystemConfig::getRootWebSiteFolder()+m_routingTable[path] :
                SystemConfig::getRootWebSiteFolder()+m_routingTable["/"];

    QFile _file(_path);
    _file.open(QIODevice::ReadOnly);
    m_byteData = _file.readAll();
    _file.close();
    return m_byteData;
}

const QByteArray &NaiSysMethodHandler::post(const QString &path, const QByteArray &data)
{
    this->m_byteData = QByteArray("");
    auto v  = QString(path);
    v.replace("/","");
    QFile put_file(SystemConfig::getRootWebSiteFolder()
                   +SystemConfig::readConfigFile().value("Post-Dir").toString()+'_'+v+'_'+QString::number(rand()));

    qDebug() << put_file.fileName();
    if(put_file.open(QIODevice::WriteOnly)){
        put_file.write(data);
        put_file.close();
        m_byteData = QByteArray("{Message: Received successfully}");
    }
    else qDebug() << "File can't opened";
    return m_byteData;
}

const QByteArray &NaiSysMethodHandler::put() const
{
    return m_byteData;
}

} // namespace NaiSys
