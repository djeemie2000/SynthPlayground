TARGET = TestCommandStackLib
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp \ 
    TestCommandStackDistributor.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../UnitTest


LIBS += -lCommandStackLib -lUnitTest

debug {
    LIBS += -L./../build-dir/Debug/CommandStackLib
    LIBS += -L./../build-dir/Debug/UnitTest
    DESTDIR = ../build-dir/Debug/TestCommandStackLib
}
release {
    LIBS += -L./../build-dir/Release/CommandStackLib
    LIBS += -L./../build-dir/Release/UnitTest
    DESTDIR = ../build-dir/Release/TestCommandStackLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
