# Copyright (c) 2016 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.
# 저작권

# updated 2021-12-16 PioneerRedwood, for cef-grogu
# removed Linux/Mac OS 

# Must be loaded via FindCEF.cmake.
# FindCEF.cmake에 의해 로드돼야함
if(NOT DEFINED _CEF_ROOT_EXPLICIT)
  message(FATAL_ERROR "Use find_package(CEF) to load this file.")
endif()

#
# Shared configuration.
# 공유 설정
#

# Determine the platform.
# 플랫폼 OS_WINDOWS 사용
set(OS_WINDOWS 1)

# Determine the project architecture.
# 프로젝트 아키텍처 지정
if(NOT DEFINED PROJECT_ARCH)
  if(OS_WINDOWS AND "${CMAKE_GENERATOR_PLATFORM}" STREQUAL "arm64")
    set(PROJECT_ARCH "arm64")
  elseif(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PROJECT_ARCH "x86_64")
  else()
    set(PROJECT_ARCH "x86")
  endif()
endif()

if(${CMAKE_GENERATOR} STREQUAL "Ninja")
  set(GEN_NINJA 1)
elseif(${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
  set(GEN_MAKEFILES 1)
endif()

# Determine the build type.
# 빌드 유형 지정
if(NOT CMAKE_BUILD_TYPE AND (GEN_NINJA OR GEN_MAKEFILES))
  # CMAKE_BUILD_TYPE should be specified when using Ninja or Unix Makefiles.
  # CMAKE_BUILD_TYPE: Ninja 혹은 Unix Makefiles 중 하나를 사용하도록 명시돼야 합니다.
  set(CMAKE_BUILD_TYPE Release)
  # set(CMAKE_BUILD_TYPE DEBUG)
  message(WARNING "No CMAKE_BUILD_TYPE value selected, using ${CMAKE_BUILD_TYPE}")
endif()


# Path to the include directory.
set(CEF_INCLUDE_PATH "${_CEF_ROOT}")

# Path to the libcef_dll_wrapper target.
set(CEF_LIBCEF_DLL_WRAPPER_PATH "${_CEF_ROOT}/libcef_dll")


# Shared compiler/linker flags.
list(APPEND CEF_COMPILER_DEFINES
  # C++ 표준에 없는 C99 표준 stdint.h 매크로를 사용하도록 허용
  # Allow C++ programs to use stdint.h macros specified in the C99 standard that aren't 
  # in the C++ standard (e.g. UINT8_MAX, INT64_MIN, etc)
  __STDC_CONSTANT_MACROS __STDC_FORMAT_MACROS
  )


# Configure use of the sandbox. SET OFF 
option(USE_SANDBOX "Enable or disable use of the sandbox." OFF)

#
# Windows configuration.
#

if(OS_WINDOWS)
  if (GEN_NINJA)
	# Ninja를 사용할 경우 CMake 기본들을 클리어. 콘솔 경고 초과를 피하기 위해
    # When using the Ninja generator clear the CMake defaults to avoid excessive
    # console warnings (see issue #2120).
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
  endif()

  if(USE_SANDBOX)
    # Check if the current MSVC version is compatible with the cef_sandbox.lib
    # static library. We require VS2015 or newer.
    if(MSVC_VERSION LESS 1900)
      message(WARNING "CEF sandbox is not compatible with the current MSVC version (${MSVC_VERSION})")
      set(USE_SANDBOX OFF)
    endif()
  endif()

  # Consumers who run into LNK4099 warnings can pass /Z7 instead (see issue #385).
  set(CEF_DEBUG_INFO_FLAG "/Zi" CACHE STRING "Optional flag specifying specific /Z flag to use")

  # Consumers using different runtime types may want to pass different flags
  set(CEF_RUNTIME_LIBRARY_FLAG "/MT" CACHE STRING "Optional flag specifying which runtime to use")
  if (CEF_RUNTIME_LIBRARY_FLAG)
    list(APPEND CEF_COMPILER_FLAGS_DEBUG ${CEF_RUNTIME_LIBRARY_FLAG})
    list(APPEND CEF_COMPILER_FLAGS_RELEASE ${CEF_RUNTIME_LIBRARY_FLAG})
  endif()

  # Platform-specific compiler/linker flags.
  set(CEF_LIBTYPE STATIC)
  list(APPEND CEF_COMPILER_FLAGS
    /MP           # Multiprocess compilation
    /Gy           # Enable function-level linking
    /GR-          # Disable run-time type information
    /W4           # Warning level 4
    /WX           # Treat warnings as errors
    /wd4100       # Ignore "unreferenced formal parameter" warning
    /wd4127       # Ignore "conditional expression is constant" warning
    /wd4244       # Ignore "conversion possible loss of data" warning
    /wd4324       # Ignore "structure was padded due to alignment specifier" warning
    /wd4481       # Ignore "nonstandard extension used: override" warning
    /wd4512       # Ignore "assignment operator could not be generated" warning
    /wd4701       # Ignore "potentially uninitialized local variable" warning
    /wd4702       # Ignore "unreachable code" warning
    /wd4996       # Ignore "function or variable may be unsafe" warning
    ${CEF_DEBUG_INFO_FLAG}
    )
  list(APPEND CEF_COMPILER_FLAGS_DEBUG
    /RTC1         # Disable optimizations
    /Od           # Enable basic run-time checks
    )
  list(APPEND CEF_COMPILER_FLAGS_RELEASE
    /O2           # Optimize for maximum speed
    /Ob2          # Inline any suitable function
    /GF           # Enable string pooling
    )
  list(APPEND CEF_LINKER_FLAGS_DEBUG
    /DEBUG        # Generate debug information
    )
  list(APPEND CEF_EXE_LINKER_FLAGS
    /MANIFEST:NO        # No default manifest (see ADD_WINDOWS_MANIFEST macro usage)
    /LARGEADDRESSAWARE  # Allow 32-bit processes to access 3GB of RAM
    )
  list(APPEND CEF_COMPILER_DEFINES
    WIN32 _WIN32 _WINDOWS             # Windows platform
    UNICODE _UNICODE                  # Unicode build
    WINVER=0x0601 _WIN32_WINNT=0x601  # Targeting Windows 7
    NOMINMAX                          # Use the standard's templated min/max
    WIN32_LEAN_AND_MEAN               # Exclude less common API declarations
    _HAS_EXCEPTIONS=0                 # Disable exceptions
    )
  list(APPEND CEF_COMPILER_DEFINES_RELEASE
    NDEBUG _NDEBUG                    # Not a debug build
    )

  # Standard libraries. 표준 라이브러리
  set(CEF_STANDARD_LIBS
    comctl32.lib
    gdi32.lib
    rpcrt4.lib
    shlwapi.lib
    ws2_32.lib
    )

  # CEF directory paths. CEF 디렉토리 경로
  set(CEF_RESOURCE_DIR        "${_CEF_ROOT}/Resources")
  set(CEF_BINARY_DIR          "${_CEF_ROOT}/$<CONFIGURATION>")
  set(CEF_BINARY_DIR_DEBUG    "${_CEF_ROOT}/Debug")
  set(CEF_BINARY_DIR_RELEASE  "${_CEF_ROOT}/Release")

  # CEF library paths.
  set(CEF_LIB_DEBUG   "${CEF_BINARY_DIR_DEBUG}/libcef.lib")
  set(CEF_LIB_RELEASE "${CEF_BINARY_DIR_RELEASE}/libcef.lib")

  # List of CEF binary files. CEF 이진 파일 리스트
  set(CEF_BINARY_FILES
    chrome_elf.dll
    libcef.dll
    libEGL.dll
    libGLESv2.dll
    snapshot_blob.bin
    v8_context_snapshot.bin
    vk_swiftshader.dll
    vk_swiftshader_icd.json
    vulkan-1.dll
    swiftshader
    )

  if(NOT PROJECT_ARCH STREQUAL "arm64")
    list(APPEND CEF_BINARY_FILES
      d3dcompiler_47.dll
      )
  endif()

  # List of CEF resource files. CEF 리소스 파일 리스트
  set(CEF_RESOURCE_FILES
    chrome_100_percent.pak
    chrome_200_percent.pak
    resources.pak
    icudtl.dat
    locales
    )
  # SANDBOX를 사용할 경우 
  if(USE_SANDBOX)
    list(APPEND CEF_COMPILER_DEFINES
      PSAPI_VERSION=1   # Required by cef_sandbox.lib
      CEF_USE_SANDBOX   # Used by apps to test if the sandbox is enabled
      )
    list(APPEND CEF_COMPILER_DEFINES_DEBUG
      _HAS_ITERATOR_DEBUGGING=0   # Disable iterator debugging
      )

    # Libraries required by cef_sandbox.lib.
    set(CEF_SANDBOX_STANDARD_LIBS
      Advapi32.lib
      dbghelp.lib
      Delayimp.lib
      OleAut32.lib
      PowrProf.lib
      Propsys.lib
      psapi.lib
      SetupAPI.lib
      Shell32.lib
      version.lib
      wbemuuid.lib
      winmm.lib
      )

    # CEF sandbox library paths.
    set(CEF_SANDBOX_LIB_DEBUG "${CEF_BINARY_DIR_DEBUG}/cef_sandbox.lib")
    set(CEF_SANDBOX_LIB_RELEASE "${CEF_BINARY_DIR_RELEASE}/cef_sandbox.lib")
  endif()

  # Configure use of ATL. ATL 사용 설정
  option(USE_ATL "Enable or disable use of ATL." ON)
  if(USE_ATL)
    # Locate the atlmfc directory if it exists. It may be at any depth inside
    # the VC directory. The cl.exe path returned by CMAKE_CXX_COMPILER may also
    # be at different depths depending on the toolchain version
    # (e.g. "VC/bin/cl.exe", "VC/bin/amd64_x86/cl.exe",
    # "VC/Tools/MSVC/14.10.25017/bin/HostX86/x86/cl.exe", etc).
    set(HAS_ATLMFC 0)
    get_filename_component(VC_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
    get_filename_component(VC_DIR_NAME ${VC_DIR} NAME)
    while(NOT ${VC_DIR_NAME} STREQUAL "VC")
      get_filename_component(VC_DIR ${VC_DIR} DIRECTORY)
      if(IS_DIRECTORY "${VC_DIR}/atlmfc")
        set(HAS_ATLMFC 1)
        break()
      endif()
      get_filename_component(VC_DIR_NAME ${VC_DIR} NAME)
    endwhile()

    # Determine if the Visual Studio install supports ATL.
    if(NOT HAS_ATLMFC)
      message(WARNING "ATL is not supported by your VC installation.")
      set(USE_ATL OFF)
    endif()
  endif()

  if(USE_ATL)
    list(APPEND CEF_COMPILER_DEFINES
      CEF_USE_ATL   # Used by apps to test if ATL support is enabled
      )
  endif()
endif()
