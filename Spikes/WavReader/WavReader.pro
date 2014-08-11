TARGET = WavReader
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp 
SOURCES += ReadWavFile.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#INCLUDEPATH += ./../../SynthLib

#CONFIG(debug, debug|release) {
#    LIBS += -L./../build-dir/Debug/SynthLib
#    PRE_TARGETDEPS += ./../../build-dir/Debug/SynthLib/libSynthLib.a
#}
#CONFIG(release, debug|release) {
#    LIBS += -L./../build-dir/Release/SynthLib
#    PRE_TARGETDEPS += ./../../build-dir/Release/SynthLib/libSynthLib.a
#}

#LIBS += -lSynthLib

#CONFIG(debug, debug|release) {
#    DESTDIR = ../build-dir/Debug/WavReader
#}
#CONFIG(release, debug|release) {
#    DESTDIR = ../build-dir/Release/WavReader
#}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
