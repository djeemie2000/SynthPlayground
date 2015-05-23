TARGET = PatchLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)

SOURCES += PatchReader.cpp \
    PatchWriter.cpp \
    PatchManager.cpp
    
HEADERS += PatchReader.h \
    PatchWriter.h \
    PatchManager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./../TinyXml2
INCLUDEPATH += ./../Utilities
INCLUDEPATH += ./../JackLib
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../ModularLib


CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/PatchLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/PatchLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

