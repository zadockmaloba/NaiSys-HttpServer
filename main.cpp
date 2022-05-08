#include <QCoreApplication>
#include "naisyshttpserver.h"
#include "naisyshttpsserver.h"
#include "systemconfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto const config = NaiSys::SystemConfig::readConfigFile();
    NaiSys::NaiSysHttpServer httpServer(
                {config.value("Port").toString().toInt(), config.value("Address").toString()}
                );

    httpServer.startServer();

    NaiSys::NaiSysHttpsServer serv2(
                {config.value("HTTPs-Port").toString().toInt(), config.value("HTTPs-Address").toString()}
                );

    serv2.startServer();

    return a.exec();
}
