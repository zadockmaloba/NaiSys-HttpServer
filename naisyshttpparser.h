#ifndef NAISYS_NAISYSHTTPPARSER_H
#define NAISYS_NAISYSHTTPPARSER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

#include "naisysdefs.h"
#include "naisysmethodhandler.h"
#include "naisyshttpresponse.h"
#include "naisyshttprequest.h"

namespace NaiSys {

class HttpParser
{
public:
    HttpParser();
    explicit HttpParser(const NaiSysHttpRequest &request);
    explicit HttpParser(const NaiSysHttpResponse &response);
    const NaiSysHttpResponse renderHttp();
    const NaiSysHttpResponse getDefaultResponse();


    DesirializedData &desirialized();
    void setDesirialized(const DesirializedData &newDesirialized);

public://static methods
    static const DesirializedData getDesirializedData(QByteArray &data);
    static const QJsonObject getJsonHeader(const QByteArray &header);
    bool keepAlive() const;

private:
    DesirializedData m_desirialized;
    bool m_keepAlive;
};

} // namespace NaiSys

#endif // NAISYS_NAISYSHTTPPARSER_H
