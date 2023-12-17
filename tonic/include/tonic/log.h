#pragma once

#include <stdio.h>
#include <stdarg.h>

namespace tonic
{
enum class log_level
{
    LOG_LVL_MSG,
    LOG_LVL_INFO,
    LOG_LVL_WARN,
    LOG_LVL_ERROR,
};

void log_main(log_level level, const char *fmt, ...);
}

#if defined(TONIC_PLAT_WINDOWS)
#define TONIC_BREAK() __debugbreak()
#elif defined(TONIC_PLAT_MACOS)
#define TONIC_BREAK() __builtin_debugtrap()
#elif defined(TONIC_PLAT_LINUX)
#define TONIC_BREAK() __builtin_trap()
#else
#define TONIC_BREAK() (void*)0
#endif

#if defined(TONIC_CONFIG_DEBUG)
#define TONIC_MSG(...) ::tonic::log_main(::tonic::log_level::LOG_LVL_MSG, __VA_ARGS__)
#define TONIC_INFO(...) ::tonic::log_main(::tonic::log_level::LOG_LVL_INFO, __VA_ARGS__)
#define TONIC_WARN(...) ::tonic::log_main(::tonic::log_level::LOG_LVL_WARN, __VA_ARGS__)
#define TONIC_ERROR(...) ::tonic::log_main(::tonic::log_level::LOG_LVL_ERROR, __VA_ARGS__)
#define TONIC_ASSERT(B, msg) if (!(B)) { ::tonic::log_main(::tonic::log_level::LOG_LVL_ERROR, "ASSERT - %s\n%s\nfile: %s\nline: %i", #B, msg, __FILE__, __LINE__); TONIC_BREAK(); }
#else
#define TONIC_MSG(...) (void*)0
#define TONIC_INFO(...) (void*)0
#define TONIC_WARN(...) (void*)0
#define TONIC_ERROR(...) (void*)0
#define TONIC_ASSERT(...) (void*)0
#endif

