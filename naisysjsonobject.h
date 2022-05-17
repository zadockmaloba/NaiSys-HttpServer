#ifndef NAISYS_NAISYSJSONOBJECT_H
#define NAISYS_NAISYSJSONOBJECT_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

#include <QSqlQueryModel>
#include <QSqlRecord>

namespace NaiSys {

class NaiSysJsonObject : public QObject
{
    Q_OBJECT
public:
    explicit NaiSysJsonObject(QObject *parent = nullptr);

signals:

public:
    static QByteArray qryModelToJson(const QSqlQueryModel* mdl, const QString _call = "NaN");
    static QStringList jsonDocToStringArr(const QByteArray& _data);

private:
    QJsonObject *m_jobj;
};


} // namespace NaiSys

#endif // NAISYS_NAISYSJSONOBJECT_H
