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
    auto const db = new DatabaseHandler;
    auto const jObj = QJsonDocument::fromJson(data).object();
    auto const v  = QString(path).replace("/","");

    db->setDbName(SystemConfig::getRootWebSiteFolder()
                 +SystemConfig::readConfigFile().value("DataBase").toString());
    db->setDbConnectionName(QString::number(rand()));
    db->initialiseDb();

    db->createAndOrInsertRowToTable(v, jObj);

    this->m_byteData = QByteArray("");

    QFile put_file(SystemConfig::getRootWebSiteFolder()
                   +SystemConfig::readConfigFile().value("Post-Dir").toString()+'_'+v+'_'+QString::number(rand()));

    qDebug() << put_file.fileName();
    if(put_file.open(QIODevice::WriteOnly)){
        put_file.write(data);
        put_file.close();
        m_byteData = QByteArray(QJsonDocument(QJsonObject({
                                                {"ResultCode", QJsonValue(0)},
                                                {"ResultDesc", QJsonValue("Accepted")}
                                            })).toJson());
    }
    else qDebug() << "File can't opened";
    return m_byteData;
}

const QByteArray &NaiSysMethodHandler::put() const
{
    return m_byteData;
}

} // namespace NaiSys
