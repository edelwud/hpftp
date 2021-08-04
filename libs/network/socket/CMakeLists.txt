create_module(
        TYPE library
        VERSION 0.0.1
        DESCRIPTION Network socket connection library
        DEPENDENCIES CONAN_PKG::libuv exceptions
        EXPORT
            CMAKE NO
            PKGCONF YES
)