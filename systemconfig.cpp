#include "systemconfig.h"

namespace NaiSys {

SystemConfig::SystemConfig()
{

}

const QString &SystemConfig::rootConfigFolder() const
{return m_rootConfigFolder;}

void SystemConfig::setRootConfigFolder(const QString &newRootConfigFolder)
{m_rootConfigFolder = newRootConfigFolder;}

const QString &SystemConfig::rootWebSiteFolder() const
{return m_rootWebSiteFolder;}

void SystemConfig::setRootWebSiteFolder(const QString &newRootWebSiteFolder)
{m_rootWebSiteFolder = newRootWebSiteFolder;}

const QString &SystemConfig::appName() const
{return m_appName;}

void SystemConfig::setAppName(const QString &newAppName)
{m_appName = newAppName;}

const QJsonObject SystemConfig::m_sInitData = {
    {"App-Name", QJsonValue("Default")},
    {"Address", QJsonValue("localhost")},
    {"Port", QJsonValue("1234")},
    {"HTTPs-Address", QJsonValue("localhost")},
    {"HTTPs-Port", QJsonValue("443")},
    {"Root-Dir", QJsonValue("www")},
    {"Landing-Page", QJsonValue("index.html")},
    {"DataBase", QJsonValue("test.sqlite")},
    {"Post-Dir", QJsonValue("post")},
    {"Put-Dir", QJsonValue("put")},
    {"Ssl-Cert", QJsonValue("/root/cert.pem")},
    {"Ssl-Key", QJsonValue("/root/key.pem")}
};

bool SystemConfig::checkForFile(const QString &filename)
{return QFile(filename).exists();}

bool SystemConfig::checkForFolder(const QString &folderpath)
{return QDir(folderpath).exists();}

void SystemConfig::createRootConfigFolder()
{

}

QJsonObject SystemConfig::readConfigFile()
{
    if(!checkForFile(__doc_dir__ +'/'+ m_sRootConfigFolder +'/'+ m_sConfigFile))
    {
        qDebug() << "File does not exist";
        createConfigFile();
        createRootWebsiteFolder("");
    }
    QFile _file(__doc_dir__ +'/'+ m_sRootConfigFolder +'/'+ m_sConfigFile);
    _file.open(QIODevice::ReadOnly);
    auto const js = QJsonDocument::fromJson(_file.readAll()).object();
    _file.close();
    return js;
}

QString SystemConfig::getRootWebSiteFolder()
{
    return __doc_dir__+'/'+ m_sRootConfigFolder+'/'+ m_sRootWebSiteFolder+'/';
}

void SystemConfig::createRootWebsiteFolder([[maybe_unused]]const QString &foldername)
{
    auto _r = QDir(__doc_dir__).mkpath(__doc_dir__+'/'+ m_sRootConfigFolder+'/'
                                       + m_sRootWebSiteFolder+'/');
    if(_r){
        QFile _file(__doc_dir__+'/'+ m_sRootConfigFolder +'/'+ m_sRootWebSiteFolder+'/'
                    + m_sInitData.value("Landing-Page").toString());
        _file.open(QIODevice::WriteOnly);
        _file.close();
    }

    QDir(__doc_dir__).mkdir(__doc_dir__+'/'+ m_sRootConfigFolder+'/'
                            + m_sRootWebSiteFolder
                            + m_sInitData.value("Post-Dir").toString());

    QDir(__doc_dir__).mkdir(__doc_dir__+ m_sRootConfigFolder+'/'
                            + m_sRootWebSiteFolder
                            + m_sInitData.value("Put-Dir").toString());

    qDebug() << QString((_r == true ) ? "Succesfully Created" : "Failed to Create");
    return;
}

void SystemConfig::createConfigFile()
{
    auto _r = QDir(__doc_dir__).mkpath(__doc_dir__+'/'+ m_sRootConfigFolder +'/');
    qDebug() << QString((_r == true ) ? "Succesfully Created" : "Failed to Create");
    if(_r){
        QFile _file(__doc_dir__+'/'+ m_sRootConfigFolder +'/'+ m_sConfigFile);
        _file.open(QIODevice::WriteOnly);
        _file.write(QJsonDocument(m_sInitData).toJson());
        _file.close();
    }
    return;
}

} // namespace NaiSys
