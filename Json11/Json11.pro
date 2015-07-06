#-------------------------------------------------
#
# Project created by QtCreator 2014-05-10T10:26:12
#
#-------------------------------------------------

QT       -= core gui

TARGET = Json11
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)

SOURCES += \
    json11.cpp 

HEADERS += \
    json11.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Json11
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Json11
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
