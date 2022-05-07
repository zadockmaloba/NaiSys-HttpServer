#include "naisysmethodhandler.h"

namespace NaiSys {

NaiSysMethodHandler::NaiSysMethodHandler(QObject *parent)
    : QObject{parent}
{
}

const QByteArray &NaiSysMethodHandler::get(const QString &path)
{
    qDebug() << path;
    QFile _file(SystemConfig::getRootWebSiteFolder()+m_routingTable[path]);

    _file.open(QIODevice::ReadOnly);
    m_byteData = _file.readAll();
    _file.close();
    return m_byteData;
}

const QByteArray &NaiSysMethodHandler::post(const QString &path, const QByteArray &data) const
{

}

const QByteArray &NaiSysMethodHandler::put() const
{

}

} // namespace NaiSys
