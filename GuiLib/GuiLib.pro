
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = GuiLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)

SOURCES += GuiUtilities.cpp \
    QGuiCallbacks.cpp \
    GuiItems.cpp \
    QView.cpp \
    QScopeWidget.cpp \
    QKeyboardWidget.cpp \
    QAudioIoDevice.cpp \
    QAudioDeviceWidget.cpp \
    QCommandSender.cpp \
    QCommandStackHandler.cpp

HEADERS += GuiUtilities.h \
    QGuiCallbacks.h \
    GuiItems.h \
    QView.h \
    QScopeWidget.h \
    QKeyboardWidget.h \
    QAudioIoDevice.h \
    QAudioDeviceWidget.h \
    QCommandSender.h \
    QCommandStackHandler.h

FORMS += \
    QScopeWidget.ui \
    QKeyboardWidget.ui \
    QAudioDeviceWidget.ui

INCLUDEPATH += ./../SynthLib ./../CommandStackLib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#debug:LIBS += -L./../build-dir/Debug/SynthLib
#release:LIBS += -L./../build-dir/Release/SynthLib

#LIBS += -lSynthLib

debug:DESTDIR = ../build-dir/Debug/GuiLib
release:DESTDIR = ../build-dir/Release/GuiLib

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

