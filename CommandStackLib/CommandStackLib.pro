
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CommandStackLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)

SOURCES += QCommandSender.cpp \
    QCommandStackHandler.cpp \
    CommandStack.cpp \
    CommandStackController.cpp \
    LogCommandStackHandler.cpp \
    ExportCommandStackHandler.cpp \
    CommandStackImporter.cpp \
    ExecuteCommandStackHandler.cpp \
    MultiCommandStackHandler.cpp \
    CommandStackDistributor.cpp

HEADERS += QCommandSender.h \
    CommandStack.h \
    QCommandStackHandler.h \
    CommandStackController.h \
    CommandStackHandlerI.h \
    ImporterI.h \
    LogCommandStackHandler.h \
    ExporterI.h \
    ExportCommandStackHandler.h \
    CommandStackImporter.h \
    ExecuteCommandStackHandler.h \
    MultiCommandStackHandler.h \
    RegisterNamedCommandStackHandlerI.h \
    CommandStackDistributor.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#debug:LIBS += -L./../build-dir/Debug/SynthLib
#release:LIBS += -L./../build-dir/Release/SynthLib

debug:DESTDIR = ../build-dir/Debug/CommandStackLib
release:DESTDIR = ../build-dir/Release/CommandStackLib

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

