#ifndef NAISYS_SYSTEMCONFIG_H
#define NAISYS_SYSTEMCONFIG_H

#define __doc_dir__ QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)

#include <QObject>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

#include <string>

namespace NaiSys {

class SystemConfig
{
public:
    SystemConfig();
    const QString &rootConfigFolder() const;
    void setRootConfigFolder(const QString &newRootConfigFolder);
    const QString &rootWebSiteFolder() const;
    void setRootWebSiteFolder(const QString &newRootWebSiteFolder);
    const QString &appName() const;
    void setAppName(const QString &newAppName);

public: //static methods
    static bool checkForFile(const QString &filename);
    static bool checkForFolder(const QString &folderpath);
    static void createRootConfigFolder();
    static QJsonObject readConfigFile();
    static QString getRootWebSiteFolder();

    char *sRootWebSiteFolder() const;
    void setSRootWebSiteFolder(char *newSRootWebSiteFolder);

private:
    static void createRootWebsiteFolder(const QString &foldername = "www");
    static void createConfigFile();

private:
    static constexpr char m_sRootConfigFolder[] {"NaiSys-HttpServer"};
    static constexpr char m_sRootWebSiteFolder[] {"www"};
    static constexpr char m_sConfigFile[] {"webconfig.json"};
    static const QJsonObject m_sInitData;

private:
    QString m_rootConfigFolder;
    QString m_rootWebSiteFolder;
    QString m_appName;
};

} // namespace NaiSys

#endif // NAISYS_SYSTEMCONFIG_H
