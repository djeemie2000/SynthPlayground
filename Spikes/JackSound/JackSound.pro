TARGET = JackSound
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -ljack

debug {
    DESTDIR = ../build-dir/Debug/JackSound
}
release {
    DESTDIR = ../build-dir/Release/JackSound
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
