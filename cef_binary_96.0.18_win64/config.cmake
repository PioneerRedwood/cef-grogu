#
# Build environment configuration file for QCefView
#
message(STATUS "## Build environment configuration file for QtCefView ##")

#
# The Qt SDK path
#
set(QT_SDK_DIR
  # Change this value to the Qt SDK path of your build environment
  "C:\\SDK\\Qt\\6.2.2\\msvc2019_64"
  )
message(STATUS "## QT SDK dir: ${QT_SDK_DIR}")

#
# The CEF SDK path
#
set(CEF_SDK_DIR 
  # this must be in the same(or sub) directories in the top-level CMakeLists file
  "${CMAKE_CURRENT_SOURCE_DIR}/dep/cef_binary_96.0.18+gfe551e4+chromium-96.0.4664.110_windows64"
  )
# output
message(STATUS "## CEF SDK dir: ${CEF_SDK_DIR}")

message(STATUS "## Build environment configuration file for QtCefView ##")

