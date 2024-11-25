cmake_minimum_required (VERSION 3.13)

project(state_tracerAnalyzer)

add_definitions( -DLOGIC2 )

# enable generation of compile_commands.json, helpful for IDEs to locate include files.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# custom CMake Modules are located in the cmake directory.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(ExternalAnalyzerSDK)

set(SOURCES 
src/state_tracerAnalyzer.cpp
src/state_tracerAnalyzer.h
src/state_tracerAnalyzerResults.cpp
src/state_tracerAnalyzerResults.h
src/state_tracerAnalyzerSettings.cpp
src/state_tracerAnalyzerSettings.h
src/state_tracerSimulationDataGenerator.cpp
src/state_tracerSimulationDataGenerator.h
)

add_analyzer_plugin(${PROJECT_NAME} SOURCES ${SOURCES})
