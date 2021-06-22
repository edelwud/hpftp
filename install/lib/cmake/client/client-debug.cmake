#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "client::client" for configuration "Debug"
set_property(TARGET client::client APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(client::client PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libclient.so.0.0.1"
  IMPORTED_SONAME_DEBUG "libclient.so.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS client::client )
list(APPEND _IMPORT_CHECK_FILES_FOR_client::client "${_IMPORT_PREFIX}/lib/libclient.so.0.0.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
