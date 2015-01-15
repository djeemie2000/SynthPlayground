TARGET = Granular
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

debug {
    DESTDIR = ../build-dir/Debug/Granular
}
release {
    DESTDIR = ../build-dir/Release/Granular
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
