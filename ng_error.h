#ifndef ng_error_h
#define ng_error_h

#ifndef ng_forward_h
#include "ng_forward.h"
#endif // ng_forward_h

static inline char *ng_error_get_relative_path (char *file) {
    char *unix_search = strrchr (file, '/');
    char *unix_file = unix_search ? unix_search + 1 : file;
    char *windows_search = strrchr (unix_file, '\\');
    return windows_search ? windows_search + 1 : unix_file;
}

#define ng_error(message) fprintf (stderr, "Error (%s@%s:%d): %s\n", \
    __FUNCTION__, ng_error_get_relative_path (__FILE__), __LINE__, message);

#endif // ng_error_h
