#include "naisysmethodhandler.h"

namespace NaiSys {

MethodHandler::MethodHandler()
{

}

MethodHandler::MethodHandler(const DesirializedData &data)
    : m_desirialized{data}
{

}

const NaiSysHttpResponse MethodHandler::get()
{
    if(m_desirialized._header.contains("Content-Length"))
    {
        if(m_desirialized._header.value("Content-Type")
                .toString().contains("naisys/sql"))
        {
            qDebug() << "sql request";

            auto const qrymdl = DatabaseHandler(QString::number(rand()),
                                                SystemConfig::getRootWebSiteFolder()
                                                +SystemConfig::readConfigFile().value("DataBase").toString())
                    .runSqlQuerry(QString::fromUtf8(m_desirialized._body));
            auto const jresp = NaiSysJsonObject::qryModelToJson(qrymdl);

            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", jresp);//TODO: Find a better method
            postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "application/json");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
        else if(m_desirialized._header.value("Content-Type")
                .toString().contains("naisys/nsquerry"))
        {
            qDebug() << "custom request";

            auto const qry = this->querryParser(m_desirialized._body);
            auto const qrymdl = DatabaseHandler(QString::number(rand()),
                                                SystemConfig::getRootWebSiteFolder()
                                                +SystemConfig::readConfigFile().value("DataBase").toString())
                    .runSqlQuerry(*qry);
            auto const jresp = NaiSysJsonObject::qryModelToJson(qrymdl);

            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", jresp);//TODO: Find a better method
            postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "application/json");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
        else if(m_desirialized._header.value("Content-Type")
                .toString().contains("application/json"))
        {
            qDebug() << "json request";
            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", "<h1> NaiSys | Server </h1>");//TODO: Find a better method
            postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "text/plain");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
        else if(m_desirialized._header.value("Content-Type")
                .toString().contains("text/plain"))
        {
            qDebug() << "plain text request";
            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", "<h1> NaiSys | Server </h1>");//TODO: Find a better method
            postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "text/plain");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
        else if(m_desirialized._header.value("Content-Type")
                .toString().contains("text/html"))
        {
            qDebug() << "html request";
            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", "<h1> NaiSys | Server </h1>");//TODO: Find a better method
            postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "text/plain");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
    }
    else if(!m_desirialized._header.contains("Content-Length"))
    {
        if(m_desirialized._header.value("Accept").toString().contains("text/html")){
            qDebug() << "html request";
            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", "<h1> NaiSys | Server </h1>");//TODO: Find a better method
            postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "text/html");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
    }
    return NaiSysHttpResponse("HTTP/1.1 400 Bad\r\n", "");
}

const NaiSysHttpResponse MethodHandler::post()
{
    if(m_desirialized._header.contains("Content-Length"))
    {
        if(m_desirialized._header.value("Content-Type")
                .toString().contains("naisys/sql"))
        {
            qDebug() << "sql request";

            auto const qrymdl = DatabaseHandler(QString::number(rand()),
                                                SystemConfig::getRootWebSiteFolder()
                                                +SystemConfig::readConfigFile().value("DataBase").toString())
                    .runSqlQuerry(QString::fromUtf8(m_desirialized._body));
            auto const jresp = NaiSysJsonObject::qryModelToJson(qrymdl);

            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", jresp);//TODO: Find a better method
            //postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "application/json");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
        else if(m_desirialized._header.value("Content-Type")
                .toString().contains("naisys/nsquerry"))
        {
            qDebug() << "custom request";

            auto const qry = this->querryParser(m_desirialized._body);
            auto qrymdl = DatabaseHandler(QString::number(rand()),
                                                SystemConfig::getRootWebSiteFolder()
                                                +SystemConfig::readConfigFile().value("DataBase").toString())
                    .runSqlQuerry(*qry);
            auto const jresp = NaiSysJsonObject::qryModelToJson(qrymdl);

            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", jresp);//TODO: Find a better method
            //postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "application/json");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
        else if(m_desirialized._header.value("Content-Type")
                .toString().contains("application/json"))
        {
            qDebug() << "json request";

            QByteArray m_byteData;

            auto const path = m_desirialized._header.value("Path").toString().replace("/", "");

            auto const jObj = QJsonDocument::fromJson(m_desirialized._body).object();

            auto const resp = DatabaseHandler(QString::number(rand()),
                                                SystemConfig::getRootWebSiteFolder()
                                                +SystemConfig::readConfigFile().value("DataBase").toString())
                    .createAndOrInsertRowToTable(path,jObj);

            qDebug() << "[JSON POST STATUS]: "<< resp;

            QFile put_file(SystemConfig::getRootWebSiteFolder()
                               +SystemConfig::readConfigFile()
                           .value("Post-Dir").toString()+'/'+path+'_'+QDate::currentDate()
                           .toString()
                           .toLower()
                           .replace(" ","_"));

            qDebug() << put_file.fileName();
                if(put_file.open(QIODevice::WriteOnly | QIODevice::Append)){
                    put_file.write(m_desirialized._body);
                    put_file.close();
                    m_byteData = QByteArray(QJsonDocument(QJsonObject({
                                                            {"ResultCode", QJsonValue(0)},
                                                            {"ResultDesc", QJsonValue("Accepted")}
                                                        })).toJson());
                }
                else qDebug() << "File can't opened";

            NaiSysHttpResponse postResp("HTTP/1.1 200 Ok\r\n", m_byteData);//TODO: Find a better method
            //postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "application/json");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            return postResp;
        }
        else if(m_desirialized._header.value("Content-Type")
                .toString().contains("text/plain"))
        {
            qDebug() << "text request";
            qDebug() << m_desirialized._body;
            NaiSysHttpResponse postResp("HTTP/1.1 400 Bad\r\n", "{Error: Unknown Request}");//TODO: Find a better method
            postResp.appendRawHeader("Connection", "keep-alive");
            postResp.appendDefinedHeader(DefinedHeaders::ContentType, "text/plain");
            postResp.appendDefinedHeader(DefinedHeaders::ContentLength, QString::number(postResp.body().size()).toUtf8());
            qDebug() << postResp.toByteArray();
            return postResp;
        }
    }
    else if(!m_desirialized._header.contains("Content-Length"))
    {
        return NaiSysHttpResponse("HTTP/1.1 400 Bad\r\n", "");
    }
    return NaiSysHttpResponse("HTTP/1.1 400 Bad\r\n", "");
}

const DesirializedData &MethodHandler::desirialized() const
{return m_desirialized;}

void MethodHandler::setDesirialized(const DesirializedData &newDesirializedData)
{m_desirialized = newDesirializedData;}

const NaiSysHttpResponse &MethodHandler::defaultResponse() const
{return m_defaultResponse;}

const QStringList MethodHandler::messageParser(const QString &rawMsg)
{
    return rawMsg.split("::/");
}

const QString *MethodHandler::querryParser(const QString &rawMsg)
{
    auto const varr = messageParser(rawMsg); //return the separated string as an array
    auto const x = new QString(callsArr[varr[0]]);

    if(varr.size() == 2) return &x->replace("_?1",varr[1]);

    else if(varr.size() > 2){
        const int eval = x->count("_?");
        for (int i = 1; i <= eval; ++i)
            x->replace("_?"+QString::number(i), varr[i]);
        return x;
    }
    else return x;
}

} // namespace NaiSys
