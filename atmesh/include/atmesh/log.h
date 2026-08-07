#ifndef ATMESH_LOG_H_
#define ATMESH_LOG_H_

typedef enum atmesh_log_level_e {
    ATMESH_LOG_LEVEL_TRACE,
    ATMESH_LOG_LEVEL_DEBUG,
    ATMESH_LOG_LEVEL_INFO,
    ATMESH_LOG_LEVEL_WARN,
    ATMESH_LOG_LEVEL_ERROR,
    ATMESH_LOG_LEVEL_FATAL,
} atmesh_log_level_t;

#ifdef _DEBUG

void atmesh_log(atmesh_log_level_t level, const char* func_name, const char* fmt, ...);

#define ATMESH_LOG(level, ...) atmesh_log(level, __func__, __VA_ARGS__)

#define ATMESH_TRACE(...) ATMESH_LOG(ATMESH_LOG_LEVEL_TRACE, __VA_ARGS__)
#define ATMESH_DEBUG(...) ATMESH_LOG(ATMESH_LOG_LEVEL_DEBUG, __VA_ARGS__)
#define ATMESH_INFO(...)  ATMESH_LOG(ATMESH_LOG_LEVEL_INFO,  __VA_ARGS__)
#define ATMESH_WARN(...)  ATMESH_LOG(ATMESH_LOG_LEVEL_WARN,  __VA_ARGS__)
#define ATMESH_ERROR(...) ATMESH_LOG(ATMESH_LOG_LEVEL_ERROR, __VA_ARGS__)
#define ATMESH_FATAL(...) ATMESH_LOG(ATMESH_LOG_LEVEL_FATAL, __VA_ARGS__)

#else // _DEBUG

#define ATMESH_TRACE(...) ((void)0)
#define ATMESH_DEBUG(...) ((void)0)
#define ATMESH_INFO(...)   ((void)0)
#define ATMESH_WARN(...)   ((void)0)
#define ATMESH_ERROR(...)  ((void)0)
#define ATMESH_FATAL(...)  ((void)0)

#endif // _DEBUG

#endif // ATMESH_LOG_H_
