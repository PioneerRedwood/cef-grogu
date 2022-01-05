cmake_minimum_required(VERSION 3.5)

project(Qt_tutorial VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

# Set CEF root dir and append it to CMAKE_MODULE_PATH
###############################################################
set(CEF_ROOT "${CEF_SDK_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")
###############################################################


# Config the CEF
###############################################################
add_subdirectory(cef_binary_win64)

###############################################################

set(PROJECT_SOURCES
    qcview/event.h
    qcview/protocol.h
    qcview/query.h
    qcview/query_handler.h
    qcview/view.h
    qcview/view_delegate.h
    qcview/window.h
    qcview/scheme_handler.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Qt_tutorial
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(Qt_tutorial
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    libcef_dll_wrapper
    )

target_include_directories(Qt_tutorial
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cef_binary_win64
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/qcview
    )

set(TS_FILES Qt_tutorial_ko_KR.ts)

set_target_properties(Qt_tutorial PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Qt_tutorial)
endif()
