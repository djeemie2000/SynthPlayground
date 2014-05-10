#-------------------------------------------------
#
# Project created by QtCreator 2014-05-10T10:26:12
#
#-------------------------------------------------

QT       -= core gui

TARGET = UnitTest
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    AssertException.cpp \
    Checks.cpp \
    CurrentTest.cpp \
    DeferredTestReporter.cpp \
    DeferredTestResult.cpp \
    MemoryOutStream.cpp \
    ReportAssert.cpp \
    Test.cpp \
    TestDetails.cpp \
    TestList.cpp \
    TestReporter.cpp \
    TestReporterStdout.cpp \
    TestResults.cpp \
    TestRunner.cpp \
    TimeConstraint.cpp \
    XmlTestReporter.cpp

unix {
SOURCES += Posix/SignalTranslator.cpp \
    Posix/TimeHelpers.cpp
}
win32 {
SOURCES += \
    Win32/TimeHelpers.cpp
}

HEADERS += \
    AssertException.h \
    CheckMacros.h \
    Checks.h \
    Config.h \
    CurrentTest.h \
    DeferredTestReporter.h \
    DeferredTestResult.h \
    ExecuteTest.h \
    MemoryOutStream.h \
    ReportAssert.h \
    Test.h \
    TestDetails.h \
    TestList.h \
    TestMacros.h \
    TestReporter.h \
    TestReporterStdout.h \
    TestResults.h \
    TestRunner.h \
    TestSuite.h \
    TimeConstraint.h \
    TimeHelpers.h \
    UnitTest++.h \
    XmlTestReporter.h

unix {
HEADERS += \
    Posix/SignalTranslator.h \
    Posix/TimeHelpers.h
}
win32 {
HEADERS += \
    Win32/TimeHelpers.h
}


unix {
    target.path = /usr/lib
    INSTALLS += target
}

debug:DESTDIR = ../build-dir/Debug/UnitTest
release:DESTDIR = ../build-dir/Release/UnitTest

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
