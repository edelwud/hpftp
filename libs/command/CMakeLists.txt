create_module(
        TYPE library
        VERSION 0.0.1
        DESCRIPTION Command library for parsing user input
        DEPENDENCIES CONAN_PKG::magic_enum exceptions
        EXPORT
            CMAKE YES
            PKGCONF YES
)