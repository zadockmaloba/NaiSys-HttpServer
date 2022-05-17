#ifndef NAISYSDEFS_H
#define NAISYSDEFS_H

#include <QObject>
#include <QJsonObject>
#include <QByteArray>
#include <QSslCertificate>
#include <QSslKey>

namespace NaiSys {

enum DefinedHeaders{
    ContentType,
    ContentLength,
    Authorization,
    Cookies
};

struct DesirializedData{
    QJsonObject _header;
    QByteArray _body , _raw_header;
};

struct ServerAddress{
    int _listen_port = 80;
    QString _listen_address = "127.0.0.1";
};

struct SslObject{
    QSslCertificate *_ssl_cert;
    QSslKey *_ssl_key;
};
}

#endif // NAISYSDEFS_H
