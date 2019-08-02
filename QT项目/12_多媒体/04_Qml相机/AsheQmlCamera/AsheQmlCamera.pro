QT += quick widgets multimedia gui multimediawidgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    form.cpp \
    paintwidget.cpp \
    ffm.cpp

RESOURCES += qml.qrc

INCLUDEPATH += ../../include

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    form.ui \
    paintwidget.ui

HEADERS += \
    form.h \
    paintwidget.h \
    ffm.h



win32: LIBPATH=-L$$PWD/../../lib/win64/
unix:!macx: LIBPATH=-L$$PWD/../../lib/armeabi-v7a/


LIBS += $${LIBPATH} \
    -lavformat \
    -lavcodec \
    -lavutil \
    -lswresample \
    -lswscale

#unix:!macx: LIBS += -L$$PWD/../../lib/armeabi-v7a/ -lavformat

INCLUDEPATH += $$PWD/../../lib/armeabi-v7a
DEPENDPATH += $$PWD/../../lib/armeabi-v7a
INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../lib/armeabi-v7a/libavcodec.so \
        $$PWD/../../lib/armeabi-v7a/libavfilter.so \
        $$PWD/../../lib/armeabi-v7a/libavformat.so \
        $$PWD/../../lib/armeabi-v7a/libavutil.so \
        $$PWD/../../lib/armeabi-v7a/libopencv_java4.so \
        $$PWD/../../lib/armeabi-v7a/libswresample.so \
        $$PWD/../../lib/armeabi-v7a/libswscale.so
}
