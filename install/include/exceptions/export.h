
#ifndef exceptions_EXPORT_H
#define exceptions_EXPORT_H

#ifdef exceptions_EXCEPTIONS_STATIC_DEFINE
#  define exceptions_EXPORT
#  define exceptions_NO_EXPORT
#else
#  ifndef exceptions_EXPORT
#    ifdef exceptions_EXPORTS
        /* We are building this library */
#      define exceptions_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define exceptions_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef exceptions_NO_EXPORT
#    define exceptions_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef exceptions_EXCEPTIONS_DEPRECATED
#  define exceptions_EXCEPTIONS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef exceptions_EXCEPTIONS_DEPRECATED_EXPORT
#  define exceptions_EXCEPTIONS_DEPRECATED_EXPORT exceptions_EXPORT exceptions_EXCEPTIONS_DEPRECATED
#endif

#ifndef exceptions_EXCEPTIONS_DEPRECATED_NO_EXPORT
#  define exceptions_EXCEPTIONS_DEPRECATED_NO_EXPORT exceptions_NO_EXPORT exceptions_EXCEPTIONS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef exceptions_EXCEPTIONS_NO_DEPRECATED
#    define exceptions_EXCEPTIONS_NO_DEPRECATED
#  endif
#endif

#endif /* exceptions_EXPORT_H */
