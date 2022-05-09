QT -= gui
QT += core network sql

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        connectionthread.cpp \
        databasehandler.cpp \
        main.cpp \
        naisyshttpparser.cpp \
        naisyshttprequest.cpp \
        naisyshttpresponse.cpp \
        naisyshttpserver.cpp \
        naisyshttpsserver.cpp \
        naisysmethodhandler.cpp \
        sslconnectionthread.cpp \
        systemconfig.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    connectionthread.h \
    databasehandler.h \
    naisysdefs.h \
    naisyshttpparser.h \
    naisyshttprequest.h \
    naisyshttpresponse.h \
    naisyshttpserver.h \
    naisyshttpsserver.h \
    naisysmethodhandler.h \
    sslconnectionthread.h \
    systemconfig.h
