create_library(
        "0.0.1"
        "Network socket connection library"
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tls/cert.pem ${CMAKE_CURRENT_BINARY_DIR}/tls/cert.pem @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tls/key.pem ${CMAKE_CURRENT_BINARY_DIR}/tls/key.pem @ONLY)