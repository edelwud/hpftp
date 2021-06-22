
#ifndef executor_EXPORT_H
#define executor_EXPORT_H

#ifdef executor_EXECUTOR_STATIC_DEFINE
#  define executor_EXPORT
#  define executor_NO_EXPORT
#else
#  ifndef executor_EXPORT
#    ifdef executor_EXPORTS
        /* We are building this library */
#      define executor_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define executor_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef executor_NO_EXPORT
#    define executor_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef executor_EXECUTOR_DEPRECATED
#  define executor_EXECUTOR_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef executor_EXECUTOR_DEPRECATED_EXPORT
#  define executor_EXECUTOR_DEPRECATED_EXPORT executor_EXPORT executor_EXECUTOR_DEPRECATED
#endif

#ifndef executor_EXECUTOR_DEPRECATED_NO_EXPORT
#  define executor_EXECUTOR_DEPRECATED_NO_EXPORT executor_NO_EXPORT executor_EXECUTOR_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef executor_EXECUTOR_NO_DEPRECATED
#    define executor_EXECUTOR_NO_DEPRECATED
#  endif
#endif

#endif /* executor_EXPORT_H */
