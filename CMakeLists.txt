cmake_minimum_required(VERSION 3.8)
project(machbox)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "Insource building is disabled.")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(SOURCES
    src/core.cpp
    src/main.cpp
    src/ps/src/aes.cpp
    src/ps/src/arm.cpp
    src/ps/src/clock.cpp
    src/ps/src/cp15.cpp
    src/ps/src/dmac.cpp
    src/ps/src/gpio.cpp
    src/ps/src/iphone2g.cpp
    src/ps/src/iphone3gs.cpp
    src/ps/src/power.cpp
    src/ps/src/sha1.cpp
    src/ps/src/spi.cpp
    src/ps/src/timer.cpp
    src/ps/src/usb_otg.cpp
    src/ps/src/usb_phy.cpp
    src/ps/src/vic.cpp
    src/ps/src/wdt.cpp
)
set(HEADERS
    src/core.h
    src/info.h
    src/ps/src/aes.h
    src/ps/src/arm.h
    src/ps/src/clock.h
    src/ps/src/common.h
    src/ps/src/cp15.h
    src/ps/src/dmac.h
    src/ps/src/gpio.h
    src/ps/src/iphone2g.h
    src/ps/src/iphone3gs.h
    src/ps/src/power.h
    src/ps/src/sha1.h
    src/ps/src/spi.h
    src/ps/src/timer.h
    src/ps/src/usb_otg.h
    src/ps/src/usb_phy.h
    src/ps/src/vic.h
    src/ps/src/wdt.h
)
add_executable(machbox ${SOURCES})
target_link_libraries(machbox Qt5::Core Qt5::Gui Qt5::Widgets ssl crypto)
