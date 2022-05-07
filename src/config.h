#pragma once

constexpr bool RTC_DS3231M = true;

constexpr bool DISPLAY_CIRCUITV1 = true;
constexpr bool DISPLAY_SERIAL = false;

constexpr bool VERBOSITY_WARN = false;
constexpr bool VERBOSITY_DEBUG = false;
constexpr bool VERBOSITY_INFO = false;
constexpr bool VERBOSITY_DEBUG_V = false;

constexpr bool _VERB = DISPLAY_SERIAL || VERBOSITY_WARN || VERBOSITY_INFO || VERBOSITY_WARN || VERBOSITY_DEBUG_V;

/**
 * TODO:
 * - USE A ARDUINO PIN TO DETECT IF THERE IS POWER ON THE BOARD, IF NOT, DO NOT START AND HALT THE PROGRAM
 */
