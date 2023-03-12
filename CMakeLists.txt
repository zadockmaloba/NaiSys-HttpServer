cmake_minimum_required(VERSION 3.16)

project(NaiSys-HttpServer-Bin VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++17 -stdlib=libc++")

find_package(Qt6 6.2 COMPONENTS Core Network Sql REQUIRED)

add_subdirectory(NaiSys-DesktopUtils)

qt_add_executable( NaiSys-HttpServer-Bin
    main.cpp
)

target_include_directories( NaiSys-HttpServer-Bin PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Naisys-DesktopUtils/src
)

set_target_properties( NaiSys-HttpServer-Bin PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.naisys.net
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE # If you want to enable std::cout in Windows :^)
)

#add_custom_command(
#    TARGET NaiSys-HttpServer-Bin POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_CURRENT_BINARY_DIR}/NaiSys-DesktopUtils/LibPython/pythonlib ${CMAKE_CURRENT_BINARY_DIR}/pythonlib
#)

#file(
#    COPY ${CMAKE_CURRENT_BINARY_DIR}/NaiSys-DesktopUtils/LibPython/python
#    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
#)

target_link_libraries( NaiSys-HttpServer-Bin
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
    PRIVATE Qt6::Sql
    naisyscore
    naisyshttp
    naisysserverlang
    naisysjson
    naisyssettings
    naisysconsole
)

install( TARGETS NaiSys-HttpServer-Bin
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
