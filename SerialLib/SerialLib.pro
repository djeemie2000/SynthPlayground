TARGET = SerialLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += LinuxSerialPort.cpp 

HEADERS += LinuxSerialPort.h \
	SerialPortI.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/SerialLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/SerialLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

