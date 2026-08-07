#include "atmesh/log.h"
#include <atil/platform/platform.h>
#include <stdio.h>
#include <string.h>

#ifdef _DEBUG

#define ATMESH_LOG_LEVEL_COLOR_TRACE  ATIL_TERMFG(1,1,1,0)
#define ATMESH_LOG_LEVEL_COLOR_DEBUG  ATIL_TERMFG(1,0,1,0)
#define ATMESH_LOG_LEVEL_COLOR_INFO   ATIL_TERMFG(0,1,0,1)
#define ATMESH_LOG_LEVEL_COLOR_WARN   ATIL_TERMFG(1,1,0,1)
#define ATMESH_LOG_LEVEL_COLOR_ERROR  ATIL_TERMFG(1,0,0,0)
#define ATMESH_LOG_LEVEL_COLOR_FATAL  ATIL_TERMFG(1,0,0,1)

#define ATMESH_LOG_BUFFER_SIZE 2048

static inline atil_platform_term_color_t _color_for_level(atmesh_log_level_t level) {
    switch (level) {
        case ATMESH_LOG_LEVEL_TRACE: return ATMESH_LOG_LEVEL_COLOR_TRACE;
        case ATMESH_LOG_LEVEL_DEBUG: return ATMESH_LOG_LEVEL_COLOR_DEBUG;
        case ATMESH_LOG_LEVEL_INFO:  return ATMESH_LOG_LEVEL_COLOR_INFO;
        case ATMESH_LOG_LEVEL_WARN:  return ATMESH_LOG_LEVEL_COLOR_WARN;
        case ATMESH_LOG_LEVEL_ERROR: return ATMESH_LOG_LEVEL_COLOR_ERROR;
        case ATMESH_LOG_LEVEL_FATAL: return ATMESH_LOG_LEVEL_COLOR_FATAL;
    }

    // invalid log level
    ATMESH_FATAL("log level %d is not valid", level);
    return 0;
}

static inline const char* atmesh_prefix_for_level(atmesh_log_level_t level) {
    switch (level) {
        case ATMESH_LOG_LEVEL_TRACE: return "[ATMESH/TRACE] ";
        case ATMESH_LOG_LEVEL_DEBUG: return "[ATMESH/DEBUG] ";
        case ATMESH_LOG_LEVEL_INFO:  return "[ATMESH/INFO ] ";
        case ATMESH_LOG_LEVEL_WARN:  return "[ATMESH/WARN ] ";
        case ATMESH_LOG_LEVEL_ERROR: return "[ATMESH/ERROR] ";
        case ATMESH_LOG_LEVEL_FATAL: return "[ATMESH/FATAL] ";
        default:                    return "[ATMESH/UNKNOWN] ";
    }
}

void atmesh_log(atmesh_log_level_t level, const char* func_name, const char* fmt, ...) {
    char buffer[ATMESH_LOG_BUFFER_SIZE];

    // prefix
    const char* prefix = atmesh_prefix_for_level(level);
    size_t prefix_len = strlen(prefix);

    memcpy(buffer, prefix, prefix_len);

    // format message
    __builtin_va_list args;
    __builtin_va_start(args, fmt);

    // writes: "[INFO] [func] msg"
    int written = __builtin_snprintf(
        buffer + prefix_len,
        ATMESH_LOG_BUFFER_SIZE - prefix_len,
        "[%s] ",
        func_name
    );

    __builtin_vsnprintf(
        buffer + prefix_len + written,
        ATMESH_LOG_BUFFER_SIZE - prefix_len - written,
        fmt,
        args
    );

    __builtin_va_end(args);

    // choose color
    atil_platform_term_color_t color = _color_for_level(level);

    // route to stdout or stderr
    if (level >= ATMESH_LOG_LEVEL_ERROR)
        atil_platform_terminal_err(color, "%s\n", buffer);
    else
        atil_platform_terminal_out(color, "%s\n", buffer);

    // fatal -> abort
    if (level == ATMESH_LOG_LEVEL_FATAL) {
        fflush(stdout);
        fflush(stderr);
#if defined(ATMESH_PLATFORM_WINDOWS)
        __debugbreak();
#else
        __builtin_trap();
#endif
    }
}

#endif // _DEBUG
