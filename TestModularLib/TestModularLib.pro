TARGET = TestModularLib
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp \ 
    TestPhasorFilter.cpp \
    TestMultiStepSequencerFilter.cpp \
    TestBasicSamplerFilter.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Controllers
INCLUDEPATH += ./../SynthLib/Looper
INCLUDEPATH += ./../ModularLib
INCLUDEPATH += ./../ModularLib/Filters
INCLUDEPATH += ./../ModularLib/Modules
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../UnitTest

LIBS += -lModularLib -lSynthLib -lUnitTest

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/SynthLib
    LIBS += -L./../build-dir/Debug/ModularLib
    LIBS += -L./../build-dir/Debug/UnitTest
    DESTDIR = ../build-dir/Debug/TestModularLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/SynthLib
    LIBS += -L./../build-dir/Release/ModularLib
    LIBS += -L./../build-dir/Release/UnitTest
    DESTDIR = ../build-dir/Release/TestModularLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
