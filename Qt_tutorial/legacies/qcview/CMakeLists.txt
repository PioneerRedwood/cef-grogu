# 
# QtCefView
# 

cmake_minimum_required(VERSION 3.19.1)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY OS_FOLDERS ON)
set(OS_WINDOWS 1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)

project(QtCefView)

################################################################
# Third party config
# CEF
set(USE_SANDBOX OFF)
option(USE_SANDBOX "Enable CEF Sandbox" OFF)

# Change this value to the Qt SDK path of your build environment
# OR make it download
set(CEF_ROOT "C:/Users/Redwood/source/repos/cef-grogu/cef_binary_96.0.18_win64")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")
#
# Load the CEF configuration.
#

# Execute FindCEF.cmake which must exist in CMAKE_MODULE_PATH.
find_package(CEF REQUIRED)

#
# Define CEF-based targets.
#

# Include the libcef_dll_wrapper target.
# Comes from the libcef_dll/CMakeLists.txt file in the binary distribution
# directory.
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

message(STATUS "CEF SDK dir: ${CEF_SDK_DIR}")

# Qt
set(QT_SDK_DIR
  # Change this value to the Qt SDK path of your build environment
  "C:/SDK/Qt/6.2.2/msvc2019_64"
  )
message(STATUS "## QT SDK dir: ${QT_SDK_DIR}")

set(QtCefView_INCLUDE_PATH
  "${CEF_INCLUDE_PATH}"
  "${CMAKE_CURRENT_SOURCE_DIR}/browser"
  "${CMAKE_CURRENT_SOURCE_DIR}/common"
#   Qt?
  )

# go to test subdirectories
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test")
  add_subdirectory(test)
endif()

################################################################


