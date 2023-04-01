/**
 *  Server Executable main file
 *  Zadock Maloba <zadockmaloba@outlook.com>, 2023
 *
*/

#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonArray>

#include <naisyshttpserver.h>
#include <systemconfig.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString ver = "NaiSys-HttpServer_v0.1.0";
    qDebug() << ver;
    NaiSys::SystemConfig::setRootFolderName(ver);
    if(!NaiSys::SystemConfig::checkForConfigFile()){
        NaiSys::SystemConfig::insertToConfigFile
                ("Enabled-Sites", QJsonArray{
                     QJsonObject{
                         {"Name", "default-site"},
                         {"Port", 1234},
                         {"Address", "localhost"},
                         {"Ssl", false},
                         {"Ssl-Cert", ""},
                         {"Ssl-Key", ""},
                         {"Entry-Script", "default.nsl"},
                         {"Site-Dir", NaiSys::SystemConfig::getRootApplicationFolder()}
                     }
                 });
    }

    auto const config = NaiSys::SystemConfig::readConfigFile();

    for(auto const &obj : config.value("Enabled-Sites").toArray().toVariantList()){
        auto const v =obj.toJsonObject();
        qDebug() << v.value("Name");
        auto const serv = new NaiSys::NaiSysHttpServer();
        serv->setServerParams({
                                  .Port = v.value("Port").toInt(1234),
                                  .Ssl = v.value("Ssl").toBool(),
                                  .Address = v.value("Address").toString(),
                                  .Ssl_Cert = v.value("Ssl-Cert").toString(),
                                  .Ssl_Key = v.value("Ssl-Key").toString(),
                                  .Entry_Script = v.value("Entry-Script").toString(),
                                  .Site_Dir = v.value("Site-Dir").toString()
                              });
        serv->startServer();
    }

    return a.exec();
}
