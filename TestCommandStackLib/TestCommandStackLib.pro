TARGET = TestCommandStackLib
TEMPLATE = app
CONFIG += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \ 
    TestCommandStackDistributor.cpp \
    TestCommandStackItem.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../UnitTest


LIBS += -lCommandStackLib -lUnitTest

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/CommandStackLib
    LIBS += -L./../build-dir/Debug/UnitTest
    DESTDIR = ../build-dir/Debug/TestCommandStackLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/CommandStackLib
    LIBS += -L./../build-dir/Release/UnitTest
    DESTDIR = ../build-dir/Release/TestCommandStackLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
