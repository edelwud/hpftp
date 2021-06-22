
#ifndef client_EXPORT_H
#define client_EXPORT_H

#ifdef client_CLIENT_STATIC_DEFINE
#  define client_EXPORT
#  define client_NO_EXPORT
#else
#  ifndef client_EXPORT
#    ifdef client_EXPORTS
        /* We are building this library */
#      define client_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define client_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef client_NO_EXPORT
#    define client_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef client_CLIENT_DEPRECATED
#  define client_CLIENT_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef client_CLIENT_DEPRECATED_EXPORT
#  define client_CLIENT_DEPRECATED_EXPORT client_EXPORT client_CLIENT_DEPRECATED
#endif

#ifndef client_CLIENT_DEPRECATED_NO_EXPORT
#  define client_CLIENT_DEPRECATED_NO_EXPORT client_NO_EXPORT client_CLIENT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef client_CLIENT_NO_DEPRECATED
#    define client_CLIENT_NO_DEPRECATED
#  endif
#endif

#endif /* client_EXPORT_H */
