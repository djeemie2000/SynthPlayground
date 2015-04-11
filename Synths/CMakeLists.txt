cmake_minimum_required (VERSION 2.6)
project(ModularSynths)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_subdirectory(../UnitTest ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/UnitTest)
add_subdirectory(../TinyXml2 ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/TinyXml2)
add_subdirectory(../SerialLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/SerialLib)

add_subdirectory(../JackLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/JackLib)
add_subdirectory(../AlsaLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/AlsaLib)
add_subdirectory(../SynthLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/SynthLib)
add_subdirectory(../ModularLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ModularLib)
add_subdirectory(../CommandStackLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/CommandStackLib)
add_subdirectory(../MidiLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/MidiLib)

add_subdirectory(../TestCommandStackLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/TestCommandStackLib)
add_subdirectory(../TestSynthLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/TestSynthLib)
add_subdirectory(../TestModularLib ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/TestModularLib)

add_subdirectory(../Serial2AlsaMidiTool ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Serial2AlsaMidiTool)
add_subdirectory(../AlsaMidiLoggerTool ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/AlsaMidiLoggerTool)
add_subdirectory(../JackMidiLoggerTool ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/JackMidiLoggerTool)
add_subdirectory(../JackConnectionTool ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/JackConnectionTool)

add_subdirectory(../ModularHeadless ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/ModularHeadless)

#MESSAGE(STATUS "${PROJECT_SOURCE_DIR}/../SerialLib")
#MESSAGE(STATUS "${CMAKE_CURRENT_BINARY_DIR}/SerialLib")
