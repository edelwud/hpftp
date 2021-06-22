
#ifndef command_EXPORT_H
#define command_EXPORT_H

#ifdef command_COMMAND_STATIC_DEFINE
#  define command_EXPORT
#  define command_NO_EXPORT
#else
#  ifndef command_EXPORT
#    ifdef command_EXPORTS
        /* We are building this library */
#      define command_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define command_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef command_NO_EXPORT
#    define command_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef command_COMMAND_DEPRECATED
#  define command_COMMAND_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef command_COMMAND_DEPRECATED_EXPORT
#  define command_COMMAND_DEPRECATED_EXPORT command_EXPORT command_COMMAND_DEPRECATED
#endif

#ifndef command_COMMAND_DEPRECATED_NO_EXPORT
#  define command_COMMAND_DEPRECATED_NO_EXPORT command_NO_EXPORT command_COMMAND_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef command_COMMAND_NO_DEPRECATED
#    define command_COMMAND_NO_DEPRECATED
#  endif
#endif

#endif /* command_EXPORT_H */
