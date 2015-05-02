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
    CommandStackDistributor.cpp \
    CommandStackItem.cpp \
    StackCommandStackHandler.cpp

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
    CommandStackDistributor.h \
    CommandStackItem.h \
    StackCommandStackHandler.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/CommandStackLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/CommandStackLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

