TEMPLATE = app
TARGET = TestJack
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11 (Qt5)

SOURCES += main.cpp

LIBS += -ljack

debug:DESTDIR = ../build-dir/Debug/TestJack
release:DESTDIR = ../build-dir/Release/TestJack

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR


