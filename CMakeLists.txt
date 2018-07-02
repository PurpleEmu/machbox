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
    src/ps/aes.cpp
    src/ps/arm.cpp
    src/ps/clock.cpp
    src/ps/cp15.cpp
    src/ps/dmac.cpp
    src/ps/gpio.cpp
    src/ps/iphone2g.cpp
    src/ps/iphone3gs.cpp
    src/ps/power.cpp
    src/ps/sha1.cpp
    src/ps/spi.cpp
    src/ps/timer.cpp
    src/ps/usb_otg.cpp
    src/ps/usb_phy.cpp
    src/ps/vic.cpp
    src/ps/wdt.cpp
)
set(HEADERS
    src/core.h
    src/info.h
    src/ps/aes.h
    src/ps/arm.h
    src/ps/clock.h
    src/ps/common.h
    src/ps/cp15.h
    src/ps/dmac.h
    src/ps/gpio.h
    src/ps/iphone2g.h
    src/ps/iphone3gs.h
    src/ps/power.h
    src/ps/sha1.h
    src/ps/spi.h
    src/ps/timer.h
    src/ps/usb_otg.h
    src/ps/usb_phy.h
    src/ps/vic.h
    src/ps/wdt.h
)
add_executable(machbox ${SOURCES})
target_link_libraries(machbox Qt5::Core Qt5::Gui Qt5::Widgets ssl crypto)
