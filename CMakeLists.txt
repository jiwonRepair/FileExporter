cmake_minimum_required(VERSION 3.16)
project(LibuvFileExportSample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent)

set(LIBUV_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/include")
set(LIBUV_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib/uv.lib")

add_executable(LibuvFileExportSample
    main.cpp
    LibuvFileExporter.cpp
    wifioptimizer.cpp
)

target_include_directories(LibuvFileExportSample PRIVATE ${LIBUV_INCLUDE_DIRS})
target_link_libraries(LibuvFileExportSample PRIVATE Qt6::Core Qt6::Concurrent ${LIBUV_LIBRARIES})

if (WIN32)
    target_link_libraries(LibuvFileExportSample PRIVATE setupapi wlanapi)
endif()