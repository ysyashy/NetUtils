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
INCLUDEPATH += "./winpcap/Include"
LIBS += -L./winpcap/Lib -lwpcap
LIBS += -L./winpcap/Lib -lPacket
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
    capture/CaptureItem.cpp \
    AdvanceWidget.cpp \
    capture/SystemDevice.cpp

HEADERS  += NetUtils.h\
        http/SendDataHttp.h\
        parse/ParseData.h\
        tcp/SendDataTcp.h \
    tcp/SendDataItem.h \
    parse/ParseDataTcp.h \
    parse/ParseDataPlainText.h \
    parse/ParseDataTcpItem.h \
    capture/CaptureWidget.h \
    capture/CaptureItem.h \
    AdvanceWidget.h \
    capture/SystemDevice.h \
    capture/comstruct.h

RESOURCES += \
    Resources/netutils.qrc

FORMS += \
    capture/CaptureWidget.ui \
    capture/CaptureItem.ui \
    AdvanceWidget.ui
