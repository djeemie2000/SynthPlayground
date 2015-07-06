cmake_minimum_required (VERSION 2.6)
project(ModularSynths)
ADD_DEFINITIONS(
        #-std=c++11 # or -std=c++0x
	# other flags
)

#set(BUILD_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
set(BUILD_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
MESSAGE(STATUS "BUILD_DIRECTORY : ${BUILD_DIRECTORY}")

add_subdirectory(../UnitTest ${BUILD_DIRECTORY}/UnitTest)
add_subdirectory(../TinyXml2 ${BUILD_DIRECTORY}/TinyXml2)
add_subdirectory(../Mongoose ${BUILD_DIRECTORY}/Mongoose)
add_subdirectory(../Json11 ${BUILD_DIRECTORY}/Json11)

add_subdirectory(../Utilities ${BUILD_DIRECTORY}/Utilities)
add_subdirectory(../SerialLib ${BUILD_DIRECTORY}/SerialLib)

add_subdirectory(../JackLib ${BUILD_DIRECTORY}/JackLib)
add_subdirectory(../AlsaLib ${BUILD_DIRECTORY}/AlsaLib)
add_subdirectory(../SynthLib ${BUILD_DIRECTORY}/SynthLib)
add_subdirectory(../ModularLib ${BUILD_DIRECTORY}/ModularLib)
add_subdirectory(../CommandStackLib ${BUILD_DIRECTORY}/CommandStackLib)
add_subdirectory(../MidiLib ${BUILD_DIRECTORY}/MidiLib)
add_subdirectory(../PatchLib ${BUILD_DIRECTORY}/PatchLib)

add_subdirectory(../TestCommandStackLib ${BUILD_DIRECTORY}/TestCommandStackLib)
add_subdirectory(../TestPatchLib ${BUILD_DIRECTORY}/TestPatchLib)
add_subdirectory(../TestSynthLib ${BUILD_DIRECTORY}/TestSynthLib)
add_subdirectory(../TestModularLib ${BUILD_DIRECTORY}/TestModularLib)

add_subdirectory(../Serial2AlsaMidiTool ${BUILD_DIRECTORY}/Serial2AlsaMidiTool)
add_subdirectory(../AlsaMidiLoggerTool ${BUILD_DIRECTORY}/AlsaMidiLoggerTool)
add_subdirectory(../JackMidiLoggerTool ${BUILD_DIRECTORY}/JackMidiLoggerTool)
add_subdirectory(../JackConnectionTool ${BUILD_DIRECTORY}/JackConnectionTool)
add_subdirectory(../PatchConverterTool ${BUILD_DIRECTORY}/PatchConverterTool)

add_subdirectory(../ModularHeadless ${BUILD_DIRECTORY}/ModularHeadless)
add_subdirectory(../ModularWeb ${BUILD_DIRECTORY}/ModularWeb)

MESSAGE(STATUS "PROJECT_BINARY_DIR : ${PROJECT_BINARY_DIR}")
MESSAGE(STATUS "CMAKE_BINARY_DIR : ${CMAKE_BINARY_DIR}")
MESSAGE(STATUS "CMAKE_SOURCE_DIR : ${CMAKE_SOURCE_DIR}")
MESSAGE(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "PROJECT_NAME : ${PROJECT_NAME}")
