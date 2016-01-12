
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TinyXml2
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += tinyxml2.cpp

HEADERS += tinyxml2.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/TinyXml2
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/TinyXml2
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

