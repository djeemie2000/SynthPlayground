cmake_minimum_required (VERSION 2.6)
project (SerialLib)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_library(SerialLib
    LinuxSerialPort.cpp
    LinuxSerialPort.h
    SerialPortI.h)
