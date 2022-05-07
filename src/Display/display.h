#pragma once
#include <stdint.h>
#include "../Layout/font.h"
#include "../Layout/words.h"


typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;


namespace Display {

    constexpr uint8_t N_ROWS = 16;
    constexpr uint8_t N_COLS = 16;

    constexpr color_t BLACK{0, 0, 0};
    constexpr color_t BLUE{0, 0, 255};
    constexpr color_t GREEN{0, 255, 0};
    constexpr color_t PINK{255, 0, 170};
    constexpr color_t PURPLE{170, 0, 255};
    constexpr color_t RED{255, 0, 0};
    constexpr color_t WHITE{255, 255, 255};
    constexpr color_t WWHITE{255, 255, 50};  // Warm white
    constexpr color_t YELLOW{255, 255, 0};
    constexpr color_t ORANGE{212, 165, 25};

    bool init_display();

    void clear_display_buffer();
    void apply_display_buffer();

    void add_words_to_display_buffer(const word_t** words, uint8_t words_in_buffer, color_t color);
    void add_pixels_to_display_buffer(const uint8_t* x, const uint8_t* y, uint8_t pixels_in_buffer, color_t color);
    void add_fontchar_to_display_buffer(const Layout::fontchar_t* fontchar, const color_t color, const uint8_t col_offset, const uint8_t row_offset);
}
