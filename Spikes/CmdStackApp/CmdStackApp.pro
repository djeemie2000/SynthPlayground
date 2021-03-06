QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CmdStackApp
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp\
        mainwindow.cpp \
    QCommandSender.cpp \
    CommandStack.cpp \
    QCommandStackHandler.cpp \
    AppSpecific.cpp \
    CommandStackController.cpp \
    LogCommandStackHandler.cpp \
    ExportCommandStackHandler.cpp \
    CommandStackImporter.cpp \
    ExecuteCommandStackHandler.cpp \
    MultiCommandStackHandler.cpp \
    CommandStackDistributor.cpp

HEADERS  += mainwindow.h \
    QCommandSender.h \
    CommandStack.h \
    QCommandStackHandler.h \
    AppSpecific.h \
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

FORMS    += mainwindow.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}

debug {
    DESTDIR = ../build-dir/Debug/TestSynthLib
}
release {
    DESTDIR = ../build-dir/Release/TestSynthLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
