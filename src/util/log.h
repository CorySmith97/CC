#pragma once

#include <stdio.h>
#define POSIX

#define LOG_LEVEL_GEN(ENUM) ENUM,
#define LOG_STRING_GEN(STRING) #STRING,

#define FOREACH_LOG_LEVEL(LOG_LEVEL) \
    LOG_LEVEL(warn)                  \
    LOG_LEVEL(debug)                 \
    LOG_LEVEL(info)                  \
    LOG_LEVEL(error)

#define FOREACH_LOG_LEVEL_COLOR(LOG_LEVEL) \
    LOG_LEVEL(\e[35m)                  \
    LOG_LEVEL(\e[33m)                 \
    LOG_LEVEL(\e[36m)                  \
    LOG_LEVEL(\e[31m)

enum log_level {
    FOREACH_LOG_LEVEL(LOG_LEVEL_GEN)
};

static const char* log_level_str[] = {
    FOREACH_LOG_LEVEL(LOG_STRING_GEN)
};

static const char* log_level_colors[] = {
    FOREACH_LOG_LEVEL_COLOR(LOG_STRING_GEN)
};

#ifdef POSIX
    #define LOG(_LEVEL, _STR) (printf("%s[%s]\e[0m %s\n", log_level_colors[_LEVEL], log_level_str[_LEVEL], _STR))
#else
    #define LOG(_LEVEL, _STR) (printf("[%s] %s\n",  log_level_str[_LEVEL], _STR))
#endif
