cmake_minimum_required (VERSION 3.13)
project ("Anim")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

set(_CRT_SECURE_NO_WARNINGS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS ON)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

add_executable(Anim)

target_include_directories(Anim SYSTEM PRIVATE "lib/raylib/src/")
target_include_directories(Anim PRIVATE "src/")
#target_include_directories(Anim SYSTEM PRIVATE "lib/bluetooth-serial-port/src/")
target_include_directories(Anim SYSTEM PRIVATE "lib/serial/include/")
target_include_directories(Anim SYSTEM PRIVATE "lib/entt/src/")

target_compile_features(Anim PUBLIC cxx_std_17)

#add_subdirectory(lib/bluetooth)
#target_link_libraries(Anim PUBLIC bluetoothserialport)

add_subdirectory(lib/serial)
target_link_libraries(Anim PUBLIC serial)

add_subdirectory(lib/raylib)
target_link_libraries(Anim PUBLIC raylib)

add_subdirectory(lib/entt)
cmake_policy(SET CMP0076 NEW)

add_compile_definitions(_CORE_DEBUG_)
add_subdirectory(src)