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


SOURCES += main.cpp\
        NetUtils.cpp\
        http/SendDataHttp.cpp\
        parse/ParseData.cpp\
        tcp/SendDataTcp.cpp

HEADERS  += NetUtils.h\
        http/SendDataHttp.h\
        parse/ParseData.h\
        tcp/SendDataTcp.h
