# ----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
# ----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "executor::executor" for configuration "Debug"
set_property(
  TARGET executor::executor
  APPEND
  PROPERTY IMPORTED_CONFIGURATIONS DEBUG
)
set_target_properties(
  executor::executor PROPERTIES IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libexecutor.so.0.0.1"
                                IMPORTED_SONAME_DEBUG "libexecutor.so.0"
)

list(APPEND _IMPORT_CHECK_TARGETS executor::executor)
list(APPEND _IMPORT_CHECK_FILES_FOR_executor::executor "${_IMPORT_PREFIX}/lib/libexecutor.so.0.0.1")

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
