TARGET = CommandStackLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG   += c++11 (Qt5)

SOURCES += CommandStack.cpp \
    CommandStackController.cpp \
    LogCommandStackHandler.cpp \
    ExportCommandStackHandler.cpp \
    CommandStackImporter.cpp \
    ExecuteCommandStackHandler.cpp \
    MultiCommandStackHandler.cpp \
    CommandStackDistributor.cpp

HEADERS += CommandStack.h \
    CommandStackController.h \
    CommandStackHandlerI.h \
    ImporterI.h \
    LogCommandStackHandler.h \
    ExporterI.h \
    ExportCommandStackHandler.h \
    CommandStackImporter.h \
    ExecuteCommandStackHandler.h \
    MultiCommandStackHandler.h \
    RegisterNamedCommandStackHandlerI.h \
    CommandStackDistributor.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#debug:LIBS += -L./../build-dir/Debug/SynthLib
#release:LIBS += -L./../build-dir/Release/SynthLib

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/CommandStackLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/CommandStackLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

