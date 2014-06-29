TARGET = AlsaSound
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -lasound

debug {
    DESTDIR = ../build-dir/Debug/AlsaSound
}
release {
    DESTDIR = ../build-dir/Release/AlsaSound
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
