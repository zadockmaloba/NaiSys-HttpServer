QT -= gui
QT += core network sql

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/NaiSys-HttpServer-Lib/release/ -lNaiSys-HttpServer-Lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/NaiSys-HttpServer-Lib/debug/ -lNaiSys-HttpServer-Lib
else:unix: LIBS += -L$$OUT_PWD/NaiSys-HttpServer-Lib/ -lNaiSys-HttpServer-Lib

INCLUDEPATH += $$PWD/NaiSys-HttpServer-Lib
DEPENDPATH += $$PWD/NaiSys-HttpServer-Lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/release/libNaiSys-HttpServer-Lib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/debug/libNaiSys-HttpServer-Lib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/release/NaiSys-HttpServer-Lib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/debug/NaiSys-HttpServer-Lib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/libNaiSys-HttpServer-Lib.a


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils/release/ -lNaiSys-DesktopUtils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils/debug/ -lNaiSys-DesktopUtils
else:unix: LIBS += -L$$OUT_PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils/ -lNaiSys-DesktopUtils

INCLUDEPATH += $$PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils
DEPENDPATH += $$PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils/release/libNaiSys-DesktopUtils.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils/debug/libNaiSys-DesktopUtils.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils/release/NaiSys-DesktopUtils.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils/debug/NaiSys-DesktopUtils.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/NaiSys-HttpServer-Lib/NaiSys-DesktopUtils/libNaiSys-DesktopUtils.a
