TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp


LIBS += -L$$PWD/../../lib/ -lmysqlclient

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
