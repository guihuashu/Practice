TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


INCLUDEPATH += $$PWD/../../include
LIBPATH = $$PWD/../../lib
LIBS += -L$$LIBPATH -llibmysql
