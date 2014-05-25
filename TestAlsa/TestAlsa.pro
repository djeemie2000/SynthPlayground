TEMPLATE = app
TARGET = TestAlsa
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11 (Qt5)

SOURCES += main.cpp

LIBS += -lasound

debug:DESTDIR = ../build-dir/Debug/TestAlsa
release:DESTDIR = ../build-dir/Release/TestAlsa

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR


