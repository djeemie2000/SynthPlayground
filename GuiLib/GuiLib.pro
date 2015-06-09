
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = GuiLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)

SOURCES += GuiUtilities.cpp \
    QGuiCallbacks.cpp \
    QScope.cpp \
    QCommandSender.cpp \
    QCommandStackHandler.cpp \
    GuiCommandStack.cpp \
    QScopeWidget2.cpp \
    QStatusLedWidget.cpp \
    QGraphWidget.cpp

HEADERS += GuiUtilities.h \
    QGuiCallbacks.h \
    QScope.h \
    QCommandSender.h \
    QCommandStackHandler.h \
    GuiCommandStack.h \
    QScopeWidget2.h \
    QStatusLedWidget.h \
    QGraphWidget.h

FORMS += \
    QScopeWidget2.ui

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../ModularLib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#CONFIG(debug, debug|release) {
#    LIBS += -L./../build-dir/Debug/SynthLib
#    PRE_TARGETDEPS += ./../build-dir/Debug/SynthLib/libSynthLib.a
#    LIBS += -L./../build-dir/Debug/CommandStackLib
#    PRE_TARGETDEPS += ./../build-dir/Debug/CommandStackLib/libCommandStackLib.a
#}

#LIBS += -lSynthLib
#LIBS += -lCommandStackLib

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/GuiLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/GuiLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

