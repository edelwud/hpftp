#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "exceptions::exceptions" for configuration "Debug"
set_property(TARGET exceptions::exceptions APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(exceptions::exceptions PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libexceptions.so.0.0.1"
  IMPORTED_SONAME_DEBUG "libexceptions.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS exceptions::exceptions )
list(APPEND _IMPORT_CHECK_FILES_FOR_exceptions::exceptions "${_IMPORT_PREFIX}/lib/libexceptions.so.0.0.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)