cmake_minimum_required(VERSION 3.16)

project(LibuvFileExportSample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBUV_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/include")
set(LIBUV_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib/uv.lib")



find_package(Qt6 REQUIRED COMPONENTS Gui Qml Quick Test Core Concurrent)

qt_standard_project_setup(REQUIRES 6.5)

set(QML_FILES
    Page2.qml
)

add_executable(FileExporter
    main.cpp
    SimpleFileExporter.h SimpleFileExporter.cpp
    LibuvFileExporter.cpp LibuvFileExporter.h
)
qt_add_qml_module(FileExporter
    URI FileExporter
    VERSION 1.0
    QML_FILES ${QML_FILES}
)
target_include_directories(FileExporter PRIVATE ${LIBUV_INCLUDE_DIRS})
target_link_libraries(FileExporter PRIVATE Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Core Qt6::Concurrent ${LIBUV_LIBRARIES})

if (WIN32)
    target_link_libraries(FileExporter PRIVATE setupapi wlanapi)
endif()

# install(TARGETS FileExporter
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
