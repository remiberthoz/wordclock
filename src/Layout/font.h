#pragma once
#include <stdint.h>

namespace Layout {

    constexpr uint8_t MAX_PIXELS_IN_FONTCHAR = 25;

    typedef struct {
        const uint8_t n_pixels;
        const uint8_t pixels[MAX_PIXELS_IN_FONTCHAR][2];
    } fontchar_t;

    class Font {
        public:
            constexpr static const fontchar_t ZERO = {};
            constexpr static const fontchar_t ONE = {};
            constexpr static const fontchar_t TWO = {};
            constexpr static const fontchar_t THREE = {};
            constexpr static const fontchar_t FOUR = {};
            constexpr static const fontchar_t FIVE = {};
            constexpr static const fontchar_t SIX = {};
            constexpr static const fontchar_t SEVEN = {};
            constexpr static const fontchar_t HEIGHT = {};
            constexpr static const fontchar_t NINE = {};

            constexpr static const fontchar_t D = {};
            constexpr static const fontchar_t J = {};
            constexpr static const fontchar_t L = {};
            constexpr static const fontchar_t M = {};
            constexpr static const fontchar_t S = {};
            constexpr static const fontchar_t V = {};
            constexpr static const fontchar_t a = {};
            constexpr static const fontchar_t e = {};
            constexpr static const fontchar_t i = {};
            constexpr static const fontchar_t m = {};
            constexpr static const fontchar_t n = {};
            constexpr static const fontchar_t r = {};
            constexpr static const fontchar_t u = {};
    };

    template<typename T> const fontchar_t* digit_to_fontchar(const int8_t digit);

}

#include "font.tpp"
