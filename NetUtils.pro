#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T21:30:42
#
#-------------------------------------------------

CONFIG += c++11
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetUtils
TEMPLATE = app

# winpcap
INCLUDEPATH += $$PWD/winpcap/Include

LIBS += $$PWD/winpcap/Lib/wpcap.lib
LIBS += $$PWD/winpcap/Lib/Packet.lib

# ws2_32.lib Windows Socket
LIBS += -lws2_32


SOURCES += main.cpp\
        NetUtils.cpp\
        http/SendDataHttp.cpp\
        parse/ParseData.cpp\
        tcp/SendDataTcp.cpp \
    tcp/SendDataItem.cpp \
    parse/ParseDataTcp.cpp \
    parse/ParseDataPlainText.cpp \
    parse/ParseDataTcpItem.cpp \
    capture/CaptureWidget.cpp \
    AdvanceWidget.cpp \
    capture/SystemDevice.cpp \
    capture/DumpInterface.cpp \
    capture/DumpThread.cpp \
    capture/DumpOfflineThread.cpp \
    common/UtilsConfigure.cpp

HEADERS  += NetUtils.h\
        http/SendDataHttp.h\
        parse/ParseData.h\
        tcp/SendDataTcp.h \
    tcp/SendDataItem.h \
    parse/ParseDataTcp.h \
    parse/ParseDataPlainText.h \
    parse/ParseDataTcpItem.h \
    capture/CaptureWidget.h \
    AdvanceWidget.h \
    capture/SystemDevice.h \
    capture/comstruct.h \
    capture/DumpInterface.h \
    capture/DumpThread.h \
    inline/utilsinline.h \
    capture/DumpOfflineThread.h \
    common/UtilsConfigure.h

RESOURCES += \
    Resources/netutils.qrc

FORMS += \
    capture/CaptureWidget.ui \
    AdvanceWidget.ui
