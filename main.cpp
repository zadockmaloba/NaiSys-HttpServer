#include <QCoreApplication>
#include "naisyshttpserver.h"
#include "naisyshttpsserver.h"
#include "systemconfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto const config = NaiSys::SystemConfig::readConfigFile();

    for(auto obj : config.value("Enabled-Sites").toArray()){
        auto const v =obj.toObject();
        qDebug() << v.value("Name");
        if(v.value("Ssl").toBool()){
            auto const serv = new NaiSys::NaiSysHttpsServer(
                        {v.value("Port").toInt(), config.value("Address").toString()}
                        );
            serv->setSslObj({v.value("Ssl-Cert").toString(), v.value("Ssl-Key").toString()});
            serv->startServer();
        }
        else {
            auto const serv = new NaiSys::NaiSysHttpServer(
                        {v.value("Port").toInt(), config.value("Address").toString()}
                        );
            serv->startServer();
        }
    }

    return a.exec();
}
