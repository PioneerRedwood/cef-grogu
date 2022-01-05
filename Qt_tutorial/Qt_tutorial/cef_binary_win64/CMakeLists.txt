# Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

# For VS2019 and Xcode 12+ support.
cmake_minimum_required(VERSION 3.19)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Project name.
# TODO: Change this line to match your project name when you copy this file.
#project(grogu)

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0077 NEW)

# Set the runtime library type
set(CEF_RUNTIME_LIBRARY_FLAG "/MD" CACHE STRING "Use dynamic runtime")

# Disable the SANDBOX
set(USE_SANDBOX OFF CACHE BOOL "Disable the Sandbox")

# Disable the ATL

set(USE_ATL OFF CACHE STRING "Disable the ATL")

set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")

set(CEF_SDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cef_binary_win64")

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


# Display configuration settings.
PRINT_CEF_CONFIG()
