#ifndef NAISYSDEFS_H
#define NAISYSDEFS_H

#include <QObject>
#include <QJsonObject>
#include <QByteArray>

namespace NaiSys {
struct DesirializedData{
    QJsonObject _header;
    QByteArray _body;
};
}

#endif // NAISYSDEFS_H
