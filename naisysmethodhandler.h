#ifndef NAISYS_NAISYSMETHODHANDLER_H
#define NAISYS_NAISYSMETHODHANDLER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include "systemconfig.h"

namespace NaiSys {

class NaiSysMethodHandler : public QObject
{
    Q_OBJECT
public:
    explicit NaiSysMethodHandler(QObject *parent = nullptr);
    const QByteArray& get(const QString &path);
    const QByteArray& post(const QString &path, const QByteArray& data)const;
    const QByteArray& put() const;

signals:

private:
    QString m_rootPath;
    QByteArray m_byteData;
    QMap <QString, QString> m_routingTable = {
        {"/", SystemConfig::readConfigFile().value("Landing-Page").toString()},
        {"index", SystemConfig::readConfigFile().value("Landing-Page").toString()},
	{"/favicon.ico", SystemConfig::readConfigFile().value("Landing-Page").toString()}
    };
};

} // namespace NaiSys

#endif // NAISYS_NAISYSMETHODHANDLER_H
