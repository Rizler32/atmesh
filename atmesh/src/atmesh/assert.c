#ifdef _DEBUG

#include "atmesh/assert.h"
#include <stdio.h>

void atmesh_assert_fail(const char* expr, const char* file, int line, const char* msg, ...) {
    // print base header
    fprintf(stderr, "[Orion] Assertion failed: %s, file %s, line %d: ", expr, file, line);

    // print message
    if (msg) {
        __builtin_va_list args;
        __builtin_va_start(args, msg);
        __builtin_vfprintf(stderr, msg, args);
        __builtin_va_end(args);
    }

    fprintf(stderr, "\n");

    // break in the debugger
    ATMESH_DEBUG_BREAK();
}

#endif // _DEBUG
