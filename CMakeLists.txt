cmake_minimum_required(VERSION 3.16)

project(NaiSys-HttpServer-Bin VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Core Network Sql PrintSupport Gui REQUIRED)

add_subdirectory(NaiSys-HttpServer-Lib)

qt_add_executable( NaiSys-HttpServer-Bin
    main.cpp
)

target_include_directories( NaiSys-HttpServer-Bin PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Naisys-HttpServer-Lib
    ${CMAKE_CURRENT_SOURCE_DIR}/Naisys-HttpServer-Lib/Naisys-DesktopUtils
)

set_target_properties( NaiSys-HttpServer-Bin PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries( NaiSys-HttpServer-Bin
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
    PRIVATE Qt6::Sql
    PRIVATE Qt6::PrintSupport
    PRIVATE Qt6::Gui
    NaiSys-HttpServer-Lib
    NaiSys-DesktopUtils
)

install( TARGETS NaiSys-HttpServer-Bin
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)