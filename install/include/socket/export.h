
#ifndef socket_EXPORT_H
#define socket_EXPORT_H

#ifdef socket_SOCKET_STATIC_DEFINE
#  define socket_EXPORT
#  define socket_NO_EXPORT
#else
#  ifndef socket_EXPORT
#    ifdef socket_EXPORTS
        /* We are building this library */
#      define socket_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define socket_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef socket_NO_EXPORT
#    define socket_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef socket_SOCKET_DEPRECATED
#  define socket_SOCKET_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef socket_SOCKET_DEPRECATED_EXPORT
#  define socket_SOCKET_DEPRECATED_EXPORT socket_EXPORT socket_SOCKET_DEPRECATED
#endif

#ifndef socket_SOCKET_DEPRECATED_NO_EXPORT
#  define socket_SOCKET_DEPRECATED_NO_EXPORT socket_NO_EXPORT socket_SOCKET_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef socket_SOCKET_NO_DEPRECATED
#    define socket_SOCKET_NO_DEPRECATED
#  endif
#endif

#endif /* socket_EXPORT_H */
