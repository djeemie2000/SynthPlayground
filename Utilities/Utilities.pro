TARGET = Utilities
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += FileSystemHelpers.cpp 
    
HEADERS += ClockUtilities.h \
    ContinuousThreadRunner.h \
    PeriodicThreadRunner.h \ 
    FileSystemHelpers.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Utilities
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Utilities
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

