#include "font.h"

template<typename T> const Layout::fontchar_t* Layout::digit_to_fontchar(const int8_t digit) {
    switch(digit) {
        case 0:
            return &(T::ZERO);
        case 1:
            return &(T::ONE);
        case 2:
            return &(T::TWO);
        case 3:
            return &(T::THREE);
        case 4:
            return &(T::FOUR);
        case 5:
            return &(T::FIVE);
        case 6:
            return &(T::SIX);
        case 7:
            return &(T::SEVEN);
        case 8:
            return &(T::HEIGHT);
        case 9:
            return &(T::NINE);
        default:
            return &(T::ZERO);
    }
}
