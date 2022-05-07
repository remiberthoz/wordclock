#pragma once

void printf_init();

template<typename... Args> void printf_warn(Args... args);
template<typename... Args> void printf_debug(Args... args);
template<typename... Args> void printf_info(Args... args);
template<typename... Args> void printf_debugv(Args... args);
template<typename... Args> void printf_c(Args... args);

#include "verbose.tpp"
