#ifndef __ZS_DBG_H__
#define __ZS_DBG_H__

/* Zed Shaw's Awesome Debug Macros */

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) \
    do { \
        fprintf(stderr, "DEBUG %s:%d [%s] " M "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) \
    do { \
        fprintf(stderr, "[ERROR] (%s:%d [%s]: errno: %s) " M "\n", \
                __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__); \
    } while (0)

#define log_warn(M, ...) \
    do { \
        fprintf(stderr, "[WARN] (%s:%d [%s]: errno: %s) " M "\n", \
                __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__); \
    } while (0)

#define log_info(M, ...) \
    do { \
        fprintf(stderr, "[INFO] (%s:%d [%s]) " M "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)

#define check(A, M, ...) \
    do { \
        if (!(A)) { \
            log_err(M, ##__VA_ARGS__); \
            errno = 0; \
            goto error; \
        } \
    } while (0)

#define sentinel(M, ...) \
    do { \
        log_err(M, ##__VA_ARGS__); \
        errno = 0; \
        goto error; \
    } while (0)

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) \
    do { \
        if (!(A)) { \
            debug(M, ##__VA_ARGS__); \
            errno = 0; \
            goto error; \
        } \
    } while (0)

#endif /* end of include guard: __ZS_DBG_H__ */
