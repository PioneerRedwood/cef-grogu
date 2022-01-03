# Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

# For VS2019 and Xcode 12+ support.
cmake_minimum_required(VERSION 3.19)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Project name.
# TODO: Change this line to match your project name when you copy this file.
project(grogu)

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

#
# CEF_ROOT setup.
#
# CEF DIR already exists set the root
# if(NOT EXISTS "$ENV{CEF_DIR}")
  
# elseif()
#   set(CEF_ROOT "$ENV{CEF_DIR}")
# endif()

set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
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

# Include application targets.
# Comes from the <target>/CMakeLists.txt file in the current directory.
# TODO: Change these lines to match your project target when you copy this file.
# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
#   add_subdirectory(tests/cefsimple)
#   add_subdirectory(tests/gtest)
#   add_subdirectory(tests/ceftests)
# endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cefclient")
  add_subdirectory(cefclient)
endif()

# Display configuration settings.
PRINT_CEF_CONFIG()
