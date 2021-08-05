create_module(
        TYPE library_static
        VERSION 0.0.1
        DESCRIPTION Logging module
        DEPENDENCIES CONAN_PKG::magic_enum
        EXPORT
            CMAKE NO
            PKGCONF YES
)