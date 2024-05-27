TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += core


DEFINES += ZMQ_STATIC
LIBS += -L$$PWD/../lib -lzmq -lws2_32 -lIphlpapi
INCLUDEPATH += $$PWD/../include

SOURCES += main.cpp \
    pico.cpp \
    rgb_control.cpp

HEADERS += \
    pico.h \
    rgb_control.h


