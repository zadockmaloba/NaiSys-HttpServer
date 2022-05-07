#include <QCoreApplication>
#include "naisyshttpserver.h"
#include "systemconfig.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto const config = NaiSys::SystemConfig::readConfigFile();
    NaiSys::NaiSysHttpServer httpServer(
                {config.value("Port").toString().toInt(), config.value("Address").toString()}
                );

    httpServer.startServer();

    return a.exec();
}
