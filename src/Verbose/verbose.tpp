#include <stdio.h>
#include "../config.h"

template<typename... Args> static void printf_warn(Args... args) {
    if constexpr(VERBOSITY_WARN) {
        printf("[WARNING] ");
        printf(args...);
    }
}
template<typename... Args> static void printf_warn_c(Args... args) {
    if constexpr(VERBOSITY_WARN) {
        printf(args...);
    }
}


template<typename... Args> static void printf_debug(Args... args) {
    if constexpr(VERBOSITY_DEBUG) {
        printf("[DEBUG] ");
        printf(args...);
    }
}
template<typename... Args> static void printf_debug_c(Args... args) {
    if constexpr(VERBOSITY_DEBUG) {
        printf(args...);
    }
}


template<typename... Args> static void printf_info(Args... args) {
    if constexpr(VERBOSITY_INFO) {
        printf("[INFO] ");
        printf(args...);
    }
}
template<typename... Args> static void printf_info_c(Args... args) {
    if constexpr(VERBOSITY_INFO) {
        printf(args...);
    }
}


template<typename... Args> static void printf_debugv(Args... args) {
    if constexpr(VERBOSITY_DEBUG_V) {
        printf("[DEBUG_VERBOSE] ");
        printf(args...);
    }
}
template<typename... Args> static void printf_debugv_c(Args... args) {
    if constexpr(VERBOSITY_DEBUG_V) {
        printf(args...);
    }
}
