
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = GuiLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)

SOURCES += GuiUtilities.cpp \
    QGuiCallbacks.cpp \
    GuiItems.cpp \
    QScope.cpp \
    QScopeWidget.cpp \
    QKeyboardWidget.cpp \
    QAudioIoDevice.cpp \
    QAudioDeviceWidget.cpp \
    QCommandSender.cpp \
    QCommandStackHandler.cpp \
    GuiCommandStack.cpp \
    QPatchManagerWidget.cpp \
    QScopeWidget2.cpp \
    ModularFactoryWidget.cpp

HEADERS += GuiUtilities.h \
    QGuiCallbacks.h \
    GuiItems.h \
    QScope.h \
    QScopeWidget.h \
    QKeyboardWidget.h \
    QAudioIoDevice.h \
    QAudioDeviceWidget.h \
    QCommandSender.h \
    QCommandStackHandler.h \
    GuiCommandStack.h \
    QPatchManagerWidget.h \
    QScopeWidget2.h \
    ModularFactoryWidget.h

FORMS += \
    QScopeWidget.ui \
    QKeyboardWidget.ui \
    QAudioDeviceWidget.ui \
    QPatchManagerWidget.ui \
    QScopeWidget2.ui \
    ModularFactoryWidget.ui

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

