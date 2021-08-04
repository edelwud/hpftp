create_module(
        TYPE executable
        VERSION 0.0.1
        DESCRIPTION High-processing multi-threaded FTP server
        DEPENDENCIES CONAN_PKG::openssl logger
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tls/cert.pem ${CMAKE_CURRENT_BINARY_DIR}/tls/cert.pem @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tls/key.pem ${CMAKE_CURRENT_BINARY_DIR}/tls/key.pem @ONLY)