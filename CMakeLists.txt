cmake_minimum_required(VERSION 3.20)

project(fix_artemis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/utf-8)
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(DETOURS_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/${CMAKE_GENERATOR_PLATFORM}/detours.lib")

set(ENABLE_ICONV OFF CACHE BOOL "Libiconv is not needed.")
add_subdirectory(utils)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/utils")

set(CORES dllmain.cpp)

add_library(fix_artemis SHARED ${CORES})
target_link_libraries(fix_artemis "${DETOURS_LIB}")
target_link_libraries(fix_artemis utils)

add_library(fix_artemis_proxy SHARED ${CORES} proxy.h proxy.cpp exports.def)
target_link_libraries(fix_artemis_proxy "${DETOURS_LIB}")
target_link_libraries(fix_artemis_proxy utils)
target_compile_definitions(fix_artemis_proxy PRIVATE D3D9_PROXY)
set_target_properties(fix_artemis_proxy PROPERTIES OUTPUT_NAME "d3d9")
