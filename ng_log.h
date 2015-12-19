#ifndef ng_log_h
#define ng_log_h

#ifndef ng_forward_h
#include <stdio.h>
#include <string.h>
#endif // ng_forward_h

static inline char *ng_log_get_relative_path(char *file) {
    char *unix_search = strrchr (file, '/');
    char *unix_file = unix_search ? unix_search + 1 : file;
    char *windows_search = strrchr (unix_file, '\\');
    return windows_search ? windows_search + 1 : unix_file;
}

#define ng_info(message) fprintf (stdout, "Info (%s@%s:%d): %s\n", \
    __FUNCTION__, ng_log_get_relative_path (__FILE__), __LINE__, message);

#define ng_error(message) fprintf (stderr, "Error (%s@%s:%d): %s\n", \
    __FUNCTION__, ng_log_get_relative_path (__FILE__), __LINE__, message);

#endif // ng_log_h
