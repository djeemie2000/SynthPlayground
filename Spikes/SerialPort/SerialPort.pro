TARGET = SerialPort
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp 
HEADERS +=

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#INCLUDEPATH += ../../SynthLib

#LIBS += -ljack

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/SerialPort
}
CONFIG(release, debug|release) {
   DESTDIR = ../build-dir/Release/SerialPort
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
