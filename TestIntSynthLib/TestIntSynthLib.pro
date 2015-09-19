TARGET = TestIntSynthLib
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp \
    TestIntOnePoleFilter.cpp \
    TestIntPhaseGenerator.cpp \
    TestIntOperators.cpp \
    TestIntCombinors.cpp \
    TestIntConversions.cpp \
    TestIntMultiSaw.cpp \
    TestIntOperatorFactory.cpp \
    TestIntCombinedOperator.cpp \
    TestIntSimpleOscillator.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./../IntSynthLib
INCLUDEPATH += ./../UnitTest

LIBS += -lIntSynthLib -lUnitTest

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/IntSynthLib
    LIBS += -L./../build-dir/Debug/UnitTest
    DESTDIR = ../build-dir/Debug/TestIntSynthLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/IntSynthLib
    LIBS += -L./../build-dir/Release/UnitTest
    DESTDIR = ../build-dir/Release/TestIntSynthLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
