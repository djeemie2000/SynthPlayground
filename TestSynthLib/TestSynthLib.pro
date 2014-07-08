TARGET = TestSynthLib
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp \
    TestRampUp.cpp \
    TestPeriodicConstGenerator.cpp \
    TestStepSequencer2.cpp \
    TestPerdiodicTicker.cpp \
    TestNotes.cpp \
    TestDelayLine.cpp \
    TestFeedbackDelay.cpp \
    TestAREnvelope.cpp \
    TestConstNumSamplesGenerator.cpp \
    TestPeriodicSampleGrabber.cpp \
    TestFMOperatorStage.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../UnitTest

LIBS += -lSynthLib -lUnitTest

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/SynthLib
    LIBS += -L./../build-dir/Debug/UnitTest
    DESTDIR = ../build-dir/Debug/TestSynthLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/SynthLib
    LIBS += -L./../build-dir/Release/UnitTest
    DESTDIR = ../build-dir/Release/TestSynthLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
