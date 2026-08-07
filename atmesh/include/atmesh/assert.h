#ifndef ATMESH_ASSERT_H_
#define ATMESH_ASSERT_H_

#ifdef _DEBUG

// throw an assertion failure with the given expression, file, line, and message
void atmesh_assert_fail(const char* expr, const char* file, int line, const char* msg, ...);

#ifdef _WIN32
    #include <intrin.h>
    #define ATMESH_DEBUG_BREAK() __debugbreak()
#else
    #include <signal.h>
    #define ATMESH_DEBUG_BREAK() raise(SIGTRAP)
#endif

// assert macro that checks the expression and calls atmesh_assert_fail if it fails
#define ATMESH_ASSERT(expr, ...) \
    do { \
        if (!(expr)) { \
            atmesh_assert_fail(#expr, __FILE__, __LINE__, __VA_ARGS__); \
        } \
    } while (0)

// assert macro that checks the expression and if it fails, calls atmesh_assert_fail and aborts the program
#define ATMESH_ASSERT_ABORT(expr, ...) \
    do { \
        if (!(expr)) { \
            atmesh_assert_fail(#expr, __FILE__, __LINE__, __VA_ARGS__); \
            abort(); \
        } \
    } while (0)

#else
#define ATMESH_ASSERT(...) ((void)0)
#define ATMESH_ASSERT_ABORT(...) ((void)0)

#endif // _DEBUG

#endif // ATMESH_ASSERT_H_
