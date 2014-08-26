TARGET = TestModularLib
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp \ 
    TestPhasorFilter.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./../ModularLib
INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Controllers
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../UnitTest

LIBS += -lModularLib -lUnitTest

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/ModularLib
    LIBS += -L./../build-dir/Debug/UnitTest
    DESTDIR = ../build-dir/Debug/TestModularLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/ModularLib
    LIBS += -L./../build-dir/Release/UnitTest
    DESTDIR = ../build-dir/Release/TestModularLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
