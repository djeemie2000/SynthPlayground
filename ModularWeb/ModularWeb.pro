QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = ModularWeb
TEMPLATE = app
CONFIG += console
CONFIG   += c++11 (Qt5)

SOURCES += \
    main.cpp \
    ModularWebController.cpp \
    WebPageManager.cpp \
    WebPageHelpers.cpp \
    WebPageModuleParameterVisitor.cpp \
    WebRequest.cpp \
    FileSystemHelpers.cpp \
    PatchManager.cpp

HEADERS += \
    ModularWebController.h \
    WebPageManager.h \
    WebPageHelpers.h \
    WebPageModuleParameterVisitor.h \
    WebRequest.h \
    FileSystemHelpers.h \
    PatchManager.h

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Controllers
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../ModularLib
INCLUDEPATH += ./../ModularLib/Filters
INCLUDEPATH += ./../ModularLib/Modules
INCLUDEPATH += ./../GuiLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../JackLib
INCLUDEPATH += ./../TinyXml2
INCLUDEPATH += ./../Mongoose

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/SynthLib
    PRE_TARGETDEPS += ./../build-dir/Debug/SynthLib/libSynthLib.a
    LIBS += -L./../build-dir/Debug/CommandStackLib
    PRE_TARGETDEPS += ./../build-dir/Debug/CommandStackLib/libCommandStackLib.a
    LIBS += -L./../build-dir/Debug/ModularLib
    PRE_TARGETDEPS += ./../build-dir/Debug/ModularLib/libModularLib.a
    LIBS += -L./../build-dir/Debug/GuiLib
    PRE_TARGETDEPS += ./../build-dir/Debug/GuiLib/libGuiLib.a
    LIBS += -L./../build-dir/Debug/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Debug/MidiLib/libMidiLib.a
    LIBS += -L./../build-dir/Debug/JackLib
    PRE_TARGETDEPS += ./../build-dir/Debug/JackLib/libJackLib.a
    LIBS += -L./../build-dir/Debug/TinyXml2
    PRE_TARGETDEPS += ./../build-dir/Debug/TinyXml2/libTinyXml2.a
    LIBS += -L./../build-dir/Debug/Mongoose
    PRE_TARGETDEPS += ./../build-dir/Debug/Mongoose/libMongoose.a
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/SynthLib
    PRE_TARGETDEPS += ./../build-dir/Release/SynthLib/libSynthLib.a
    LIBS += -L./../build-dir/Release/CommandStackLib
    PRE_TARGETDEPS += ./../build-dir/Release/CommandStackLib/libCommandStackLib.a
    LIBS += -L./../build-dir/Release/ModularLib
    PRE_TARGETDEPS += ./../build-dir/Release/ModularLib/libModularLib.a
    LIBS += -L./../build-dir/Release/GuiLib
    PRE_TARGETDEPS += ./../build-dir/Release/GuiLib/libGuiLib.a
    LIBS += -L./../build-dir/Release/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Release/MidiLib/libMidiLib.a
    LIBS += -L./../build-dir/Release/JackLib
    PRE_TARGETDEPS += ./../build-dir/Release/JackLib/libJackLib.a
    LIBS += -L./../build-dir/Release/TinyXml2
    PRE_TARGETDEPS += ./../build-dir/Release/TinyXml2/libTinyXml2.a
    LIBS += -L./../build-dir/Release/Mongoose
    PRE_TARGETDEPS += ./../build-dir/Release/TinyXml2/libMongoose.a
}

LIBS += -lModularLib
LIBS += -lGuiLib
LIBS += -lCommandStackLib
LIBS += -lSynthLib
LIBS += -lMidiLib
LIBS += -lJackLib
LIBS += -lTinyXml2
LIBS += -lMongoose

win32 {
    INCLUDEPATH += "C:/Program Files (x86)/Jack/includes"
    LIBS += "C:/Program Files (x86)/Jack/lib/libjack.lib"
}
unix {
    LIBS += -ljack
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/ModularWeb
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/ModularWeb
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR