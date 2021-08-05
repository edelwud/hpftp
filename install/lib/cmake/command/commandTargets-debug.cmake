# ----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
# ----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "command::command" for configuration "Debug"
set_property(
  TARGET command::command
  APPEND
  PROPERTY IMPORTED_CONFIGURATIONS DEBUG
)
set_target_properties(
  command::command
  PROPERTIES IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "exceptions::exceptions"
             IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libcommand.so.0.0.1"
             IMPORTED_SONAME_DEBUG "libcommand.so.0"
)

list(APPEND _IMPORT_CHECK_TARGETS command::command)
list(APPEND _IMPORT_CHECK_FILES_FOR_command::command "${_IMPORT_PREFIX}/lib/libcommand.so.0.0.1")

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
