# Copyright (c) 2016 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.
# 저작권

# updated 2021-12-16 by PioneerRedwood, for cef-grogu
# removed Linux/OS_MAC

# Must be loaded via FindCEF.cmake.
# FindCEF.cmake에서 로드돼야 합니다. 
if(NOT DEFINED _CEF_ROOT_EXPLICIT)
  message(FATAL_ERROR "Use find_package(CEF) to load this file.")
endif()

#
# Shared macros.
# cmake 파일들에서 공유되는 매크로
#

# Print the current CEF configuration. 현재 CEF 설정을 출력합니다.
macro(PRINT_CEF_CONFIG)
  message(STATUS "*** CEF CONFIGURATION SETTINGS ***")
  message(STATUS "Generator:                    ${CMAKE_GENERATOR}")
  message(STATUS "Platform:                     ${CMAKE_SYSTEM_NAME}")
  message(STATUS "Project architecture:         ${PROJECT_ARCH}")

  if(GEN_NINJA OR GEN_MAKEFILES)
    message(STATUS "Build type:                   ${CMAKE_BUILD_TYPE}")
  endif()

  message(STATUS "Binary distribution root:     ${_CEF_ROOT}")

  if(OS_WINDOWS)
    message(STATUS "Visual Studio ATL support:    ${USE_ATL}")
  endif()

  message(STATUS "CEF sandbox:                  ${USE_SANDBOX}")

  set(_libraries ${CEF_STANDARD_LIBS})
  if(OS_WINDOWS AND USE_SANDBOX)
    list(APPEND _libraries ${CEF_SANDBOX_STANDARD_LIBS})
  endif()
  message(STATUS "Standard libraries:           ${_libraries}")

  message(STATUS "Compile defines:              ${CEF_COMPILER_DEFINES}")
  message(STATUS "Compile defines (Debug):      ${CEF_COMPILER_DEFINES_DEBUG}")
  message(STATUS "Compile defines (Release):    ${CEF_COMPILER_DEFINES_RELEASE}")
  message(STATUS "C compile flags:              ${CEF_COMPILER_FLAGS} ${CEF_C_COMPILER_FLAGS}")
  message(STATUS "C compile flags (Debug):      ${CEF_COMPILER_FLAGS_DEBUG} ${CEF_C_COMPILER_FLAGS_DEBUG}")
  message(STATUS "C compile flags (Release):    ${CEF_COMPILER_FLAGS_RELEASE} ${CEF_C_COMPILER_FLAGS_RELEASE}")
  message(STATUS "C++ compile flags:            ${CEF_COMPILER_FLAGS} ${CEF_CXX_COMPILER_FLAGS}")
  message(STATUS "C++ compile flags (Debug):    ${CEF_COMPILER_FLAGS_DEBUG} ${CEF_CXX_COMPILER_FLAGS_DEBUG}")
  message(STATUS "C++ compile flags (Release):  ${CEF_COMPILER_FLAGS_RELEASE} ${CEF_CXX_COMPILER_FLAGS_RELEASE}")
  message(STATUS "Exe link flags:               ${CEF_LINKER_FLAGS} ${CEF_EXE_LINKER_FLAGS}")
  message(STATUS "Exe link flags (Debug):       ${CEF_LINKER_FLAGS_DEBUG} ${CEF_EXE_LINKER_FLAGS_DEBUG}")
  message(STATUS "Exe link flags (Release):     ${CEF_LINKER_FLAGS_RELEASE} ${CEF_EXE_LINKER_FLAGS_RELEASE}")
  message(STATUS "Shared link flags:            ${CEF_LINKER_FLAGS} ${CEF_SHARED_LINKER_FLAGS}")
  message(STATUS "Shared link flags (Debug):    ${CEF_LINKER_FLAGS_DEBUG} ${CEF_SHARED_LINKER_FLAGS_DEBUG}")
  message(STATUS "Shared link flags (Release):  ${CEF_LINKER_FLAGS_RELEASE} ${CEF_SHARED_LINKER_FLAGS_RELEASE}")

  if(OS_LINUX OR OS_WINDOWS)
    message(STATUS "CEF Binary files:             ${CEF_BINARY_FILES}")
    message(STATUS "CEF Resource files:           ${CEF_RESOURCE_FILES}")
  endif()
endmacro()

# Append platform specific sources to a list of sources. 플랫폼 특정 소스를 소스 리스트에 추가합니다.
macro(APPEND_PLATFORM_SOURCES name_of_list)
  if(OS_LINUX AND ${name_of_list}_LINUX)
    list(APPEND ${name_of_list} ${${name_of_list}_LINUX})
  endif()
  if(OS_POSIX AND ${name_of_list}_POSIX)
    list(APPEND ${name_of_list} ${${name_of_list}_POSIX})
  endif()
  if(OS_WINDOWS AND ${name_of_list}_WINDOWS)
    list(APPEND ${name_of_list} ${${name_of_list}_WINDOWS})
  endif()
  if(OS_MAC AND ${name_of_list}_MAC)
    list(APPEND ${name_of_list} ${${name_of_list}_MAC})
  endif()
endmacro()

# Determine the target output directory based on platform and generator. 
# 플랫폼과 생성기에 기반한 대상 출력 디렉토리를 지정합니다.
macro(SET_CEF_TARGET_OUT_DIR)
  if(GEN_NINJA OR GEN_MAKEFILES)
    # By default Ninja and Make builds don't create a subdirectory named after
    # the configuration.
    set(CEF_TARGET_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")

    # Output binaries (executables, libraries) to the correct directory.
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CEF_TARGET_OUT_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CEF_TARGET_OUT_DIR})
  else()
    set(CEF_TARGET_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>")
  endif()
endmacro()

# Copy a list of files from one directory to another. Relative files paths are maintained.
# The path component of the source |file_list| will be removed.
# 하나의 디렉토리에서 다른 곳으로 파일들을 복사, 상대 경로로 지정된 파일들은 유지됩니다.
# |file_list|의 하위 요소들은 삭제됩니다.
macro(COPY_FILES target file_list source_dir target_dir)
  foreach(FILENAME ${file_list})
    set(source_file ${source_dir}/${FILENAME})
    get_filename_component(target_name ${FILENAME} NAME)
    set(target_file ${target_dir}/${target_name})

    string(FIND ${source_file} "$<CONFIGURATION>" _pos)
    if(NOT ${_pos} EQUAL -1)
      # Must test with an actual configuration directory.
      string(REPLACE "$<CONFIGURATION>" "Release" existing_source_file ${source_file})
      if(NOT EXISTS ${existing_source_file})
        string(REPLACE "$<CONFIGURATION>" "Debug" existing_source_file ${source_file})
      endif()
    else()
      set(existing_source_file ${source_file})
    endif()

    if(IS_DIRECTORY ${existing_source_file})
      add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_file}" "${target_file}"
        VERBATIM
        )
    else()
      add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${source_file}" "${target_file}"
        VERBATIM
        )
    endif()
  endforeach()
endmacro()

#
# Windows macros.
# 윈도우 용 매크로들
#

if(OS_WINDOWS)

# Add custom manifest files to an executable target.
# 실행파일 대상에 커스텀 매니페스트 파일을 추가합니다.
macro(ADD_WINDOWS_MANIFEST manifest_path target extension)
  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND "mt.exe" -nologo
            -manifest \"${manifest_path}/${target}.${extension}.manifest\" \"${manifest_path}/compatibility.manifest\"
            -outputresource:"${CEF_TARGET_OUT_DIR}/${target}.${extension}"\;\#1
    COMMENT "Adding manifest..."
    )
endmacro()

endif(OS_WINDOWS)

#
# Target configuration macros.
# 대상 설정 매크로들
#

# Add a logical target that can be used to link the specified libraries into an
# executable target.
# 실행파일 대상에 명시된 라이브러리로 링크되어 사용할 수 있도록 논리적 대상을 추가합니다.
macro(ADD_LOGICAL_TARGET target debug_lib release_lib)
  add_library(${target} ${CEF_LIBTYPE} IMPORTED)
  set_target_properties(${target} PROPERTIES
    IMPORTED_LOCATION "${release_lib}"
    IMPORTED_LOCATION_DEBUG "${debug_lib}"
    IMPORTED_LOCATION_RELEASE "${release_lib}"
    )
endmacro()

# Set common target properties. Use SET_LIBRARY_TARGET_PROPERTIES() or
# SET_EXECUTABLE_TARGET_PROPERTIES() instead of calling this macro directly.
# 공통 타겟 특성 설정. 해당 매크로를 직접적으로 쓰기 대신에
# SET_LIBRARY_TARGET_PROPERTIES() 혹은 SET_EXECUTABLE_TARGET_PROPERTIES()를 사용할 것. 
macro(SET_COMMON_TARGET_PROPERTIES target)
  # Compile flags.
  target_compile_options(${target} PRIVATE ${CEF_COMPILER_FLAGS} ${CEF_CXX_COMPILER_FLAGS})
  target_compile_options(${target} PRIVATE $<$<CONFIG:Debug>:${CEF_COMPILER_FLAGS_DEBUG} ${CEF_CXX_COMPILER_FLAGS_DEBUG}>)
  target_compile_options(${target} PRIVATE $<$<CONFIG:Release>:${CEF_COMPILER_FLAGS_RELEASE} ${CEF_CXX_COMPILER_FLAGS_RELEASE}>)

  # Compile definitions.
  target_compile_definitions(${target} PRIVATE ${CEF_COMPILER_DEFINES})
  target_compile_definitions(${target} PRIVATE $<$<CONFIG:Debug>:${CEF_COMPILER_DEFINES_DEBUG}>)
  target_compile_definitions(${target} PRIVATE $<$<CONFIG:Release>:${CEF_COMPILER_DEFINES_RELEASE}>)

  # Include directories.
  target_include_directories(${target} PRIVATE ${CEF_INCLUDE_PATH})

  # Linker flags.
  if(CEF_LINKER_FLAGS)
    string(REPLACE ";" " " _flags_str "${CEF_LINKER_FLAGS}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS ${_flags_str})
  endif()
  if(CEF_LINKER_FLAGS_DEBUG)
    string(REPLACE ";" " " _flags_str "${CEF_LINKER_FLAGS_DEBUG}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS_DEBUG ${_flags_str})
  endif()
  if(CEF_LINKER_FLAGS_RELEASE)
    string(REPLACE ";" " " _flags_str "${CEF_LINKER_FLAGS_RELEASE}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS_RELEASE ${_flags_str})
  endif()
  
endmacro()

# Set library-specific properties.
# 라이브러리-특정 속성 설정
macro(SET_LIBRARY_TARGET_PROPERTIES target)
  SET_COMMON_TARGET_PROPERTIES(${target})

  # Shared library linker flags.
  if(CEF_SHARED_LINKER_FLAGS)
    string(REPLACE ";" " " _flags_str "${CEF_SHARED_LINKER_FLAGS}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS ${_flags_str})
  endif()
  if(CEF_SHARED_LINKER_FLAGS_DEBUG)
    string(REPLACE ";" " " _flags_str "${CEF_SHARED_LINKER_FLAGS_DEBUG}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS_DEBUG ${_flags_str})
  endif()
  if(CEF_SHARED_LINKER_FLAGS_RELEASE)
    string(REPLACE ";" " " _flags_str "${CEF_SHARED_LINKER_FLAGS_RELEASE}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS_RELEASE ${_flags_str})
  endif()
endmacro()

# Set executable-specific properties.
# 실행파일-특정 속성 설정
macro(SET_EXECUTABLE_TARGET_PROPERTIES target)
  SET_COMMON_TARGET_PROPERTIES(${target})

  # Executable linker flags.
  if(CEF_EXE_LINKER_FLAGS)
    string(REPLACE ";" " " _flags_str "${CEF_EXE_LINKER_FLAGS}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS ${_flags_str})
  endif()
  if(CEF_EXE_LINKER_FLAGS_DEBUG)
    string(REPLACE ";" " " _flags_str "${CEF_EXE_LINKER_FLAGS_DEBUG}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS_DEBUG ${_flags_str})
  endif()
  if(CEF_EXE_LINKER_FLAGS_RELEASE)
    string(REPLACE ";" " " _flags_str "${CEF_EXE_LINKER_FLAGS_RELEASE}")
    set_property(TARGET ${target} PROPERTY LINK_FLAGS_RELEASE ${_flags_str})
  endif()
endmacro()
