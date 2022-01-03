# 
# The qcview build environment
# 

cmake_minimum_required(VERSION 3.4.1)
project(qcview)

# set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Generated Files")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6 COMPONENTS Core GUI Widgets REQUIRED)

# SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${QCEF_VIEW_SDK_LIB_OUT})
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${QCEF_VIEW_SDK_LIB_OUT})

set(QCVIEW_SRCS
  browser_app.h
  browser_app.cpp
  browser_handler.h
  browser_handler.cpp
  cef_manager.h
  cef_manager.cpp
  cef_setting.h
  cef_setting.cpp
  cef_window.h
  cef_window.cpp
  event.h
  protocol.h
  qc_setting.cpp
  query_handler.h
  query_handler.cpp
  scheme_handler.h
  scheme_handler.cpp
  view.h
  view.cpp
  )
source_group(qcview FILES ${QCVIEW_SRCS})

# make the target lib
add_library(${PROJECT_NAME} STATIC 
  ${QCVIEW_SRCS}
)

# define compile
# a preprocessor can be defined here
target_compile_definitions(${PROJECT_NAME} PRIVATE
    UNICODE
    _UNICODE
    QCEFVIEW_LIB
  )

# CHECK OUT CEF LINKING LIBRARAIES WELL
message(STATUS "CEF_DLL_WRPPER: ${CEF_DLL_WRAPPER}")
message(STATUS "CEF_DLL_FILE: ${CEF_LIB_FILE}")

# linking
target_link_libraries(${PROJECT_NAME} PRIVATE
	# Qt
  Qt6::Core
	Qt6::Gui
  Qt6::Widgets
  # Cef
  ${CEF_DLL_WRAPPER}
  ${CEF_LIB_FILE}
  ${}
)


# ?
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CEF_RESOURCE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/icudtl.dat $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/icudtl.dat
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CEF_BINARY_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Include ${QCEF_VIEW_SDK_INC_OUT}
)

# 
# QCefViewTest build
# - Need to search "how to build the Qt applications"
# 

cmake_minimum_required(VERSION 3.4.1)
project(QCefViewTest)

set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Generated Files")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Qt6 components: Core // GUI // Widgets
find_package(Qt6 COMPONENTS Core GUI Widgets REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}/out/${QCEF_VIEW_DLL}
)

# source files
file(GLOB_RECURSE _SRC_FILES
  "*.h"
  "*.cpp"
  )
source_group("Source Files" ${_SRC_FILES})

file(GLOB_RECURSE _UI_FILES
  "*.ui"
  )
source_group("Form Files" ${_UI_FILES})

file(GLOB_RECURSE _RES_FILES
    "*.qrc"
    "*.rc"
  )
source_group("Resource Files" ${_RES_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${PROJECT_NAME})

add_executable(${PROJECT_NAME} WIN32
  ${_SRC_FILES}
  ${_UI_FILES}
  ${_RES_FILES}
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  UNICODE
  _UNICODE
  )
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER Test)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
	Qt6::Core
	Qt6::Gui
  Qt6::Widgets
  ${QCEF_VIEW_DLL}
)

# Embed the manifest file into the target
if (MSVC)
  if (CMAKE_MAJOR_VERSION LESS 3)
		message(WARNING "CMake version 3.0 or newer is required use build variable TARGET_FILE")
	else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND mt.exe -manifest \"${CMAKE_CURRENT_SOURCE_DIR}\\${PROJECT_NAME}.manifest\" -inputresource:\"$<TARGET_FILE:${PROJECT_NAME}>\" -outputresource:\"$<TARGET_FILE:${PROJECT_NAME}>\"
    )
  endif()
endif(MSVC)

find_program(DEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/QCefViewTestPage.html $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${QCEF_VIEW_SDK_BIN_OUT}/$<CONFIGURATION> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  # Deploy the Qt Application
  COMMAND ${DEPLOYQT_EXECUTABLE} 
  --no-svg 
  --no-translations 
  --no-compiler-runtime 
  $<TARGET_FILE:${PROJECT_NAME}>
)