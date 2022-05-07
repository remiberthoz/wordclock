#pragma once
#include "font.h"
#include <stdint.h>

namespace Layout {
    class DOTIMATRIX3 : public Font {

        public:
            constexpr static const fontchar_t ZERO = {12, {{2,1}, {1,2}, {3,2}, {1,3}, {3,3}, {1,4}, {3,4}, {1,5}, {3,5}, {1,6}, {3,6}, {2,7}}};
            constexpr static const fontchar_t ONE = {10, {{2,1}, {1,2}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6}, {1,7}, {2,7}, {3,7}}};
            constexpr static const fontchar_t TWO = {10, {{2,1}, {1,2}, {3,2}, {3,3}, {2,4}, {1,5}, {1,6}, {1,7}, {2,7}, {3,7}}};
            constexpr static const fontchar_t THREE = {9, {{2,1}, {1,2}, {3,2}, {3,3}, {2,4}, {3,5}, {1,6}, {3,6}, {2,7}}};
            constexpr static const fontchar_t FOUR = {12, {{3,1}, {2,2}, {3,2}, {1,3}, {3,3}, {1,4}, {3,4}, {1,5}, {2,5}, {3,5}, {3,6}, {3,7}}};
            constexpr static const fontchar_t FIVE = {11, {{1,1}, {2,1}, {3,1}, {1,2}, {1,3}, {1,4}, {2,4}, {3,5}, {3,6}, {2,7}, {1,7}}};
            constexpr static const fontchar_t SIX = {11, {{2,1}, {1,2}, {3,2}, {1,3}, {1,4}, {2,4}, {1,5}, {3,5}, {1,6}, {3,6}, {2,7}}};
            constexpr static const fontchar_t SEVEN = {9, {{1,1}, {2,1}, {3,1}, {3,2}, {3,3}, {2,4}, {1,5}, {1,6}, {1,7}}};
            constexpr static const fontchar_t HEIGHT = {11, {{2,1}, {1,2}, {3,2}, {1,3}, {3,3}, {2,4}, {1,5}, {3,5}, {1,6}, {3,6}, {2,7}}};
            constexpr static const fontchar_t NINE = {11, {{2,1}, {1,2}, {3,2}, {1,3}, {3,3}, {2,4}, {3,4}, {3,5}, {1,6}, {3,6}, {2,7}}};
    };
}
