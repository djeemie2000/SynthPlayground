TARGET = Mongoose
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += mongoose.c

HEADERS += mongoose.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Mongoose
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Mongoose
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

