TARGET = TestPatchLib
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./../PatchLib
INCLUDEPATH += ./../UnitTest


LIBS += -lPatchLib -lUnitTest

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/PatchLib
    LIBS += -L./../build-dir/Debug/UnitTest
    DESTDIR = ../build-dir/Debug/TestPatchLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/PatchLib
    LIBS += -L./../build-dir/Release/UnitTest
    DESTDIR = ../build-dir/Release/TestPatchLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
