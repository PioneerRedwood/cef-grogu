# 
# QCefViewTest build
# - Need to search "how to build the Qt applications"
# 

###########################################################################
# make the source group into the built project
# QtCefView/browser
file(GLOB_RECURSE QtCefView_Browser_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/../browser/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/../browser/*.cpp"
 )
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include"
  PREFIX browser
  FILES ${QtCefView_Browser_SRCS}
 )

# QtCefView/common
file(GLOB_RECURSE QtCefView_Common_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/../common/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/../common/*.cpp"
  )
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include"
  PREFIX common
  FILES ${QtCefView_Common_SRCS}
  )

add_library(QtCefView STATIC
  ${QtCefView_Browser_SRCS}
  ${QtCefView_Common_SRCS}
  )

# add include directories
target_include_directories(QtCefView PRIVATE
  ${QtCefView_INCLUDE_PATH}
  )

ADD_LOGICAL_TARGET(libcef_lib
  "${CEF_LIB_DEBUG}"
  "${CEF_LIB_RELEASE}"
  )

add_library(libcef_lib ${CEF_LIBTYPE} IMPORTED GLOBAL)
set_target_properties(libcef_lib 
  PROPERTIES
  IMPORTED_LOCATION "${CEF_LIB_RELEASE}"
  IMPORTED_LOCATION_DEBUG "${CEF_LIB_DEBUG}"
  IMPORTED_LOCATION_RELEASE "${CEF_LIB_RELEASE}"
  )

SET_LIBRARY_TARGET_PROPERTIES(QtCefView)

add_dependencies(QtCefView
  libcef_lib
  libcef_dll_wrapper
  )

set(QtCefView_LIBS
  libcef_lib
  libcef_dll_wrapper
  ${CEF_STANDARD_LIBS}
  )

# linking the libraries
target_link_libraries(QtCefView
  PUBLIC
  ${QtCefView_LIBS}
  )

###########################################################################

###########################################################################

file(GLOB_RECURSE QtCefViewTest_SRCS
  "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp"
  )
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/test"
  PREFIX test
  FILES ${QtCefViewTest_SRCS}
  )

add_executable(QtCefViewTest WIN32
  ${QtCefView_Browser_SRCS}
  ${QtCefView_Common_SRCS}
  ${QtCefViewTest_SRCS}
  )

SET_EXECUTABLE_TARGET_PROPERTIES(QtCefViewTest)
target_link_options(QtCefViewTest
  PRIVATE
  "/MANIFEST"
  )

target_include_directories(QtCefViewTest 
  PRIVATE
  ${QtCefView_INCLUDE_PATH}
  )

add_dependencies(QtCefViewTest 
  libcef_lib
  libcef_dll_wrapper
  )

set(_helper_libs
  d3d11.lib
  glu32.lib 
  imm32.lib 
  opengl32.lib
  
  libcef_lib
  libcef_dll_wrapper 
  ${CEF_STANDARD_LIBS}
  # ${CEF_SANDBOX_STANDARD_LIBS}
  )

target_link_libraries(QtCefViewTest 
  ${_helper_libs}
  )

# Add the Helper as a dependency of the main executable target.
add_dependencies(QtCefView QtCefViewTest)

# copy cef binary files
add_custom_command(TARGET QtCefViewTest POST_BUILD
  COMMAND mt.exe 
  -manifest \"${CMAKE_CURRENT_SOURCE_DIR}\\test\\QtCefViewTest.manifest\" 
  -inputresource:\"$<TARGET_FILE:QtCefViewTest>\" 
  -outputresource:\"$<TARGET_FILE:QtCefViewTest>\"
  
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CEF_RESOURCE_DIR}" "$<TARGET_FILE_DIR:QtCefViewTest>/resources"
  COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE_DIR:QtCefViewTest>/resources/icudtl.dat" "$<TARGET_FILE_DIR:QtCefViewTest>"
  COMMAND ${CMAKE_COMMAND} -E remove "$<TARGET_FILE_DIR:QtCefViewTest>/resources/icudtl.dat"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CEF_BINARY_DIR}" "$<TARGET_FILE_DIR:QtCefViewTest>"
)

###########################################################################