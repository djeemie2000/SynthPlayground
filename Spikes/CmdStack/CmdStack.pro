TARGET = CmdStack
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

debug {
    DESTDIR = ../build-dir/Debug/TestSynthLib
}
release {
    DESTDIR = ../build-dir/Release/TestSynthLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
