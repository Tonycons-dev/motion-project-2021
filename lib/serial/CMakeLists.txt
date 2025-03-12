project(serial)
add_library(serial)

target_sources(serial PRIVATE include/SerialPort.hpp)
target_include_directories(serial PRIVATE "include/")

if(WIN32) 
    target_sources(serial PRIVATE "src/windows/SerialPort.cpp")
elseif(APPLE)
    target_sources(serial PRIVATE "src/windows/SerialPort.mm")
else()
    target_sources(serial PRIVATE "src/linux/SerialPort.cpp")
endif()