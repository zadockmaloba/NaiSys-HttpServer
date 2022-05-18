#ifndef NAISYS_NAISYSMETHODHANDLER_H
#define NAISYS_NAISYSMETHODHANDLER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QString>
#include "systemconfig.h"
#include "naisysdefs.h"

#include "databasehandler.h"
#include "naisyshttpresponse.h"
#include "naisyshttprequest.h"
#include "servercalls.h"

#include "naisysjsonobject.h"
#include <QDateTime>

namespace NaiSys {

class MethodHandler
{
public:
    MethodHandler();
    explicit MethodHandler(const DesirializedData &data);
    const NaiSysHttpResponse get();
    const NaiSysHttpResponse post();

    const DesirializedData &desirialized() const;
    void setDesirialized(const DesirializedData &newDesirialized);

    const NaiSysHttpResponse &defaultResponse() const;

private://methods
    const QStringList messageParser(const QString &rawMsg);
    const QString *querryParser(const QString &rawMsg);

private:
    DesirializedData m_desirialized;
    const NaiSysHttpResponse m_defaultResponse {"HTTP/1.1 200 Ok\r\n", "{}"};
    QMap <QString, QString> m_routingTable = {
        {"/", SystemConfig::readConfigFile().value("Landing-Page").toString()},
        {"index", SystemConfig::readConfigFile().value("Landing-Page").toString()},
        {"/favicon.ico", SystemConfig::readConfigFile().value("Landing-Page").toString()}
    };
};

} // namespace NaiSys

#endif // NAISYS_NAISYSMETHODHANDLER_H
