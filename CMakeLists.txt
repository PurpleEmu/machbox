cmake_minimum_required(VERSION 3.1.0)

project(machbox)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

#properly disable insource building, as CMAKE_DISABLE_IN_SOURCE_BUILD never works for me
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "Insource building is disabled.")
endif()

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(SOURCES
src/headers/core.h
src/headers/info.h
src/core.cpp
src/main.cpp
)

add_executable(machbox WIN32 ${SOURCES})
# Use the Widgets module from Qt 5
target_link_libraries(machbox Qt5::Core Qt5::Widgets)