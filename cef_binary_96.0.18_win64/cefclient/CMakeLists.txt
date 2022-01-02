# Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

#
# Source files.
#
##########################################################################
# cefclient browser sources.
set(CEFCLIENT_BROWSER_SRCS
  browser/resource.h
  browser/resource_idmap.cc

  browser/browser_window.cc
  browser/browser_window.h
  browser/browser_window_std_win.cc
  browser/browser_window_std_win.h
  browser/client_app_browser.cc
  browser/client_app_browser.h
  browser/client_app_delegates_browser.cc
  browser/client_browser.cc
  browser/client_browser.h
  browser/client_handler.cc
  browser/client_handler.h
  browser/client_handler_std.cc
  browser/client_handler_std.h
  browser/client_types.h

  browser/main_context.cc
  browser/main_context.h
  browser/main_context_impl.cc
  browser/main_context_impl.h
  browser/main_context_impl_win.cc
  browser/main_message_loop.cc
  browser/main_message_loop.h
  browser/main_message_loop_std.cc
  browser/main_message_loop_std.h

  browser/root_window.cc
  browser/root_window.h
  browser/root_window_win.cc
  browser/root_window_win.h
  browser/temp_window.cc
  browser/temp_window.h
  browser/root_window_create.cc
  browser/root_window_manager.cc
  browser/root_window_manager.h
  )
source_group(cefclient////browser FILES ${CEFCLIENT_BROWSER_SRCS})

set(CEFCLIENT_UTILS_SRCS
  # utils
  utils/extension_util.cc
  utils/extension_util.h
  utils/file_util.cc
  utils/file_util.h
  utils/geometry_util.cc
  utils/geometry_util.h
  utils/resource_util.h
  utils/resource_util.cc
  utils/util_win.cc
  utils/util_win.h
  )
source_group(cefclient////utils FILES ${CEFCLIENT_UTILS_SRCS})

set(CEFCLIENT_TESTS_SRCS
  # tests
  tests/test_runner.cc
  tests/test_runner.h
  tests/scheme_test.cc
  tests/scheme_test.h
  tests/server_test.cc
  tests/server_test.h
  tests/urlrequest_test.cc
  tests/urlrequest_test.h
  )
source_group(cefclient////tests FILES ${CEFCLIENT_TESTS_SRCS})

# cefclient common sources.
set(CEFCLIENT_COMMON_SRCS
  common/scheme_test_common.cc
  common/scheme_test_common.h
  common/client_app.cc
  common/client_app.h
  common/client_switches.cc
  common/client_switches.h
  )
source_group(cefclient////common FILES ${CEFCLIENT_COMMON_SRCS})

# cefclient resources sources.
set(CEFCLIENT_RESOURCES_SRCS
  resources/pics/logo.png
  resources/htmls/other_tests.html
  resources/htmls/server.html
  resources/htmls/urlrequest.html
  resources/htmls/websocket.html
  # resources/htmls/grogu.html
  resources/cefclient.rc
  )
source_group(cefclient////resources FILES ${CEFCLIENT_RESOURCES_SRCS})

# cefclient entry source (for Windows)
# set(CEFCLIENT_SRC
#   cefclient.cc
#   )
# source_group(cefclient FILES ${CEFCLIENT_SRC})

set(CEFCLIENT_SRCS
  ${CEFCLIENT_BROWSER_SRCS}
  ${CEFCLIENT_COMMON_SRCS}
  ${CEFCLIENT_TESTS_SRCS}
  ${CEFCLIENT_UTILS_SRCS}
  ${CEFCLIENT_RESOURCES_SRCS}
  # ${CEFCLIENT_SRC}
  cefclient.cc
)

##########################################################################

#
# Shared configuration.
#

# Target executable names.
set(CEF_TARGET "cefclient")
ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

# Determine the target output directory.
SET_CEF_TARGET_OUT_DIR()


# boost library

if("$ENV{BOOST_SDK}")
  set(BOOST_PATH "$ENV{BOOST_SDK}")
  # include path
  set(BOOST_INCLUDE_PATH "${BOOST_PATH}/include")
  
  
  # libraray path
  # set(BOOST_STATIC_LIB_PATH "${BOOST_PATH}/stage/lib")

  set(BOOST_ASIO_SRCS

  )

else()
  message(STATUS "Required boost path in system variables")
endif()
# Example #1 header only *.hpp

# Example #2 static lib / lib

# Example #3 shared lib / dll

#
# Windows configuration.
#



# Executable target.
add_executable(${CEF_TARGET} WIN32 ${CEFCLIENT_SRCS})
SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
target_link_libraries(${CEF_TARGET} libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS} d3d11.lib glu32.lib imm32.lib opengl32.lib)

# if(USE_ATL)
#   # Required by VS2013 to link accessibility API functions.
#   target_link_libraries(${CEF_TARGET} oleacc.lib)
# endif()

# if(USE_SANDBOX)
#   # Logical target used to link the cef_sandbox library.
#   ADD_LOGICAL_TARGET("cef_sandbox_lib" "${CEF_SANDBOX_LIB_DEBUG}" "${CEF_SANDBOX_LIB_RELEASE}")
#   target_link_libraries(${CEF_TARGET} cef_sandbox_lib ${CEF_SANDBOX_STANDARD_LIBS})
# endif()

# Add the custom manifest files to the executable.
ADD_WINDOWS_MANIFEST("${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CEF_TARGET}" "exe")

# Copy CEF binary and resource files to the target output directory.
COPY_FILES("${CEF_TARGET}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
COPY_FILES("${CEF_TARGET}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")