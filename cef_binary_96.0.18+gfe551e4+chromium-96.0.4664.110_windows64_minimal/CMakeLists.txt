# CEF CMake 빌드 grogu started 2021-12-16
# 아래는 cef_binary_96.0.18+gfe551e4+chromium-96.0.4664.110_windows64_minimal 에서 windows-x64를 기반으로
# CMakeLists.txt를 수정해 빌드를 수행했습니다.
# 
# This CEF binary distribution includes the following CMake files:				해당 CEF 이진배포에는 다음의 CMake 파일들이 담겨있습니다.
#
# CMakeLists.txt              Bootstrap that sets up the CMake environment. 	CMake 환경설정을 위한 부트스트랩
# cmake/*.cmake               CEF configuration files shared by all targets. 	모든 빌드 대상에서 공유하는 CEF 설정 파일
# libcef_dll/CMakeLists.txt   Defines the libcef_dll_wrapper target.			libcef_dll_wrapper 대상을 정의
# tests/*/CMakeLists.txt      Defines the test application target.				테스트 어플리케이션 대상을 정의
#
# BUILD EXAMPLES 빌드 예시
#
# The below commands will generate project files and create a Debug build of all 
# CEF targets using CMake and the platform toolchain.
# 아래 명령어들은 프로젝트 파일을 생성하고,
# CMake와 플랫폼 툴체인을 사용해 모든 CEF 빌드 대상의 디버그 빌드를 생성합니다.
#
# 빌드 출력 디렉토리 만들고 거기서 시작
# Start by creating and entering the CMake build output directory:
# > cd path/to/cef_binary_*
# > mkdir build && cd build
#
# 64-비트 CEF 이진배포 윈도우 빌드 사용하기: VS 2019 IDE에 있는 컴파일러 사용, 툴체인
# To perform a Windows build using a 64-bit CEF binary distribution:
#   Using the Visual Studio 2019 IDE:
#     > cmake -G "Visual Studio 16" -A x64 ..
#     Open build\cef.sln in Visual Studio and select Build > Build Solution.
#
# VS2019 명령줄 도구에 있는 Ninja 사용하기
#   Using Ninja with Visual Studio 2019 command-line tools:
#     (this path may be different depending on your Visual Studio installation)
#     > "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars64.bat"
#     > cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ..
#     > ninja cefclient cefsimple

#
# Global setup.
#

# For VS2019 and Xcode 12+ support.
cmake_minimum_required(VERSION 3.19)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Project name.
# TODO: Change this line to match your project name when you copy this file.
project(CEF_GROGU)

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

#
# CEF_ROOT setup.
# This variable must be set to locate the binary distribution.
# TODO: Choose one of the below examples and comment out the rest.
#

# Example 1: The current directory contains both the complete binary
#            distribution and your project.
# A. Comment in these lines:

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
# libcef_dll_wrapper를 빌드합니다. 
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

# 2021-12-17 이미 libcef_dll_wrapper 디렉토리가 존재한다면 빌드를 수행하지 않습니다.
# if(NOT EXISTS "${CEF_LIBCEF_DLL_WRAPPER_PATH}")
#   add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)
# endif()

# Include application targets.
# Comes from the <target>/CMakeLists.txt file in the current directory.
# TODO: Change these lines to match your project target when you copy this file.
# cefgrogu 소스 디렉토리 내 프로젝트 생성, add_subdirectory()를 참고하십시오.

# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cefgrogu")
#   add_subdirectory(cefgrogu)
# endif()

# 
# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/cefclient")
#   add_subdirectory(tests/cefclient)
# endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/cefsimple")
  add_subdirectory(tests/cefsimple)
endif()

# Display configuration settings.
PRINT_CEF_CONFIG()
