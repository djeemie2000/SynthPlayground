cmake_minimum_required (VERSION 2.6)
project (UnitTest)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

if(WIN32)
set(PLATFORM_DEPENDENT_SOURCES Win32/TimeHelpers.cpp Win32/TimeHelpers.h)
endif(WIN32)

if(UNIX)
set(PLATFORM_DEPENDENT_SOURCES Posix/SignalTranslator.cpp Posix/TimeHelpers.cpp Posix/SignalTranslator.h Posix/TimeHelpers.h)
endif(UNIX)

add_library(UnitTest
    AssertException.cpp
    Checks.cpp
    CurrentTest.cpp
    DeferredTestReporter.cpp
    DeferredTestResult.cpp
    MemoryOutStream.cpp
    ReportAssert.cpp
    Test.cpp
    TestDetails.cpp
    TestList.cpp
    TestReporter.cpp
    TestReporterStdout.cpp
    TestResults.cpp
    TestRunner.cpp
    TimeConstraint.cpp
    XmlTestReporter.cpp
    AssertException.h
    CheckMacros.h
    Checks.h
    Config.h
    CurrentTest.h
    DeferredTestReporter.h
    DeferredTestResult.h
    ExecuteTest.h
    MemoryOutStream.h
    ReportAssert.h
    Test.h
    TestDetails.h
    TestList.h
    TestMacros.h
    TestReporter.h
    TestReporterStdout.h
    TestResults.h
    TestRunner.h
    TestSuite.h
    TimeConstraint.h
    TimeHelpers.h
    UnitTest++.h
    XmlTestReporter.h
    ${PLATFORM_DEPENDENT_SOURCES})

