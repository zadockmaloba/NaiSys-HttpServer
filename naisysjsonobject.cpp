#include "naisysjsonobject.h"

namespace NaiSys {

NaiSysJsonObject::NaiSysJsonObject(QObject *parent) :
    QObject(parent),
    m_jobj(new QJsonObject)
{

}

QByteArray NaiSysJsonObject::qryModelToJson(const QSqlQueryModel *mdl, [[maybe_unused]]const QString _call)
{
    QJsonObject mObj; QJsonArray jArr; QString header;

    qDebug() << mdl->rowCount();

    for(int i=0; i < mdl->rowCount(); i++){
        for(int j=0; j < mdl->columnCount(); j++){
            header = mdl->headerData(j, Qt::Horizontal).toString();
            auto xval = mdl->record(i).value(j).toString();
            mObj.insert(header, QJsonValue(xval));
        }
        jArr.append(mObj);
    }

    QJsonDocument doc(jArr);
    auto retVal = doc.toJson(QJsonDocument::Compact);
    qDebug() <<"[RESPONSE_SIZE] "<< retVal.size();
    return retVal;
}

QStringList NaiSysJsonObject::jsonDocToStringArr(const QByteArray &_data)
{
    QJsonParseError jErr; QStringList _ret;
    const auto var1 = QJsonDocument::fromJson(_data, &jErr).array().toVariantList();
    qDebug() <<"[jsonDocToStringArr(const QByteArray &_data)] "<<jErr.errorString();
    const auto var2 = var1.at(0).toMap().values();
    for(auto &v : var2) _ret.append(v.toString());
    return _ret;
}

} // namespace NaiSys
