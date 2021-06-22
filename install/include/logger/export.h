
#ifndef logger_EXPORT_H
#define logger_EXPORT_H

#ifdef logger_LOGGER_STATIC_DEFINE
#  define logger_EXPORT
#  define logger_NO_EXPORT
#else
#  ifndef logger_EXPORT
#    ifdef logger_EXPORTS
        /* We are building this library */
#      define logger_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define logger_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef logger_NO_EXPORT
#    define logger_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef logger_LOGGER_DEPRECATED
#  define logger_LOGGER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef logger_LOGGER_DEPRECATED_EXPORT
#  define logger_LOGGER_DEPRECATED_EXPORT logger_EXPORT logger_LOGGER_DEPRECATED
#endif

#ifndef logger_LOGGER_DEPRECATED_NO_EXPORT
#  define logger_LOGGER_DEPRECATED_NO_EXPORT logger_NO_EXPORT logger_LOGGER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef logger_LOGGER_NO_DEPRECATED
#    define logger_LOGGER_NO_DEPRECATED
#  endif
#endif

#endif /* logger_EXPORT_H */
