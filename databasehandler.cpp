#include "databasehandler.h"

namespace NaiSys {

DatabaseHandler::DatabaseHandler(QObject *parent)
    : QObject{parent}
{

}

DatabaseHandler::DatabaseHandler(const QSqlDatabase &dbH, QObject *parent)
    : QObject{parent},
      m_dbHandle{dbH}
{

}

DatabaseHandler::DatabaseHandler(const QString &connectionName, const QString &databaseName, QObject *parent)
    : QObject{parent},
      m_dbName{databaseName},
      m_dbConnectionName{connectionName}
{
    this->m_dbHandle = QSqlDatabase::addDatabase("QSQLITE", m_dbConnectionName);
    this->m_dbHandle.setDatabaseName(m_dbName);
}

void DatabaseHandler::initialiseDb()
{
    this->m_dbHandle = QSqlDatabase::addDatabase("QSQLITE", m_dbConnectionName);
    this->m_dbHandle.setDatabaseName(m_dbName);
}

const QSqlDatabase &DatabaseHandler::dbHandle() const
{return m_dbHandle;}

void DatabaseHandler::setDbHandle(const QSqlDatabase &newDbHandle)
{m_dbHandle = newDbHandle;}

const QString &DatabaseHandler::dbName() const
{return m_dbName;}

void DatabaseHandler::setDbName(const QString &newDbName)
{m_dbName = newDbName;}

const QString &DatabaseHandler::dbConnectionName() const
{return m_dbConnectionName;}

void DatabaseHandler::setDbConnectionName(const QString &newDbConnectionName)
{m_dbConnectionName = newDbConnectionName;}

void DatabaseHandler::reConnectDb()
{
    return; //:^}
}

bool DatabaseHandler::createAndOrInsertRowToTable(const QString &tableName, const QJsonObject &data)
{
    auto const colStringList = data.toVariantMap().keys();
    auto const valStringList = data.toVariantMap().values();

    QString colString, valString;

    for(auto const &v : colStringList) colString.append(v+",");
    colString.chop(1);

    for(auto const &v : valStringList) valString.append("'"+v.toString()+"',");
    valString.chop(1);

    auto const crt = QString("CREATE TABLE IF NOT EXISTS "+tableName+" ( "+colString+" );");

    auto const a = QString("INSERT INTO "+tableName+" ( "+colString+" ) VALUES ( "+valString+" );");

    qDebug() << a;

    this->runSqlQuerry(crt);
    this->runSqlQuerry(a);

    return 1;
}

bool DatabaseHandler::openDatabaseSocket()
{
    qDebug() << "ATTEMPTING TO CONNECT DATABASE";
    return m_dbHandle.open();
}

bool DatabaseHandler::closeDatabaseSocket()
{
    m_dbHandle.close();
    return true; //:^}
}

QSqlQueryModel *DatabaseHandler::runSqlQuerry(const QString &querry)
{
    this->openDatabaseSocket();
    auto m_model = new QSqlQueryModel; //TODO: Fix leak
    m_model->setQuery(querry, m_dbHandle);
    qDebug() << "{"+m_dbName+"} "<< "[ "+querry+" ]: "<< m_model->lastError().text();
    this->closeDatabaseSocket();
    return m_model;
}

} // namespace NaiSys
