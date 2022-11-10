#include <QCoreApplication>
#include "naisyshttpserver.h"
#include "naisyshttpsserver.h"
#include "systemconfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString ver = "NaiSys-HttpServer_v0.1.0";
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

    auto const serv = new NaiSys::NaiSysHttpServer(
                {1234, "localhost"}
                );
    serv->startServer();

//    for(auto obj : config.value("Enabled-Sites").toArray()){
//        auto const v =obj.toObject();
//        qDebug() << v.value("Name");
//        if(v.value("Ssl").toBool()){
//            auto const serv = new NaiSys::NaiSysHttpsServer(
//                        {v.value("Port").toInt(), config.value("Address").toString()}
//                        );
//            serv->setSslObj({v.value("Ssl-Cert").toString(), v.value("Ssl-Key").toString()});
//            serv->startServer();
//        }
//        else {
//            auto const serv = new NaiSys::NaiSysHttpServer(
//                        {v.value("Port").toInt(), config.value("Address").toString()}
//                        );
//            serv->startServer();
//        }
//    }

    return a.exec();
}
