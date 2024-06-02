TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT -= gui
QT += core
QT += network
QT += widgets

CONFIG += c++17 console
CONFIG -= app_bundle

DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq -lws2_32 -lIphlpapi
INCLUDEPATH += $$PWD/../include

SOURCES += main.cpp \
    pico.cpp

HEADERS += \
    pico.h


