#include "../config.h"
#include "../Display/display.h"
#include "../Layout/font.h"
#include "../Layout/words.h"
#include "display.h"
#include "CircuitV1/circuitv1.h"
#include "Serial/serial.h"


static uint8_t display_buffer[Display::N_ROWS][Display::N_COLS][3];


static void set_color_for_letter(const uint8_t row, const uint8_t col, const color_t color) {
    display_buffer[row][col][0] = color.r;
    display_buffer[row][col][1] = color.g;
    display_buffer[row][col][2] = color.b;
}


bool Display::init_display() {

    bool status = true;

    if constexpr(DISPLAY_CIRCUITV1)
        status &= CircuitV1::impl_init_display();

    if constexpr(DISPLAY_SERIAL)
        status &= Serial::impl_init_display();

    return status;
}


void Display::clear_display_buffer() {
    for (uint8_t row = 0; row < Display::N_ROWS; row++)
        for (uint8_t col = 0; col < Display::N_COLS; col++) {
            set_color_for_letter(row, col, Display::BLACK);
        }
}


void Display::apply_display_buffer() {

    if constexpr(DISPLAY_CIRCUITV1)
        CircuitV1::impl_apply_buffer(display_buffer);

    if constexpr(DISPLAY_SERIAL)
        Serial::impl_apply_buffer(display_buffer);
}


void Display::add_pixels_to_display_buffer(const uint8_t* x, const uint8_t* y, const uint8_t pixels_in_buffer, const color_t color) {
    for (uint8_t i = 0; i < pixels_in_buffer; i++) {
        set_color_for_letter(y[i], x[i], color);
    }
}


void Display::add_words_to_display_buffer(const word_t** words_buffer, const uint8_t words_in_buffer, const color_t color) {
    for (uint8_t i = 0; i < words_in_buffer; i++) {
        word_t word;
        memcpy_P(&word, words_buffer[i], sizeof(word_t));
        for (uint8_t col = word.start; col < word.start + word.length; col++) {
            set_color_for_letter(word.row, col, color);
        }
    }
}


void Display::add_fontchar_to_display_buffer(const Layout::fontchar_t* fontchar, const color_t color, const uint8_t col_offset, const uint8_t row_offset) {
    uint8_t x[Layout::MAX_PIXELS_IN_FONTCHAR];
    uint8_t y[Layout::MAX_PIXELS_IN_FONTCHAR];
    for (uint8_t i = 0; i < fontchar->n_pixels; i++) {
        x[i] = static_cast<uint8_t> ( (fontchar->pixels[i])[0] - 1 + col_offset );
        y[i] = static_cast<uint8_t> ( (fontchar->pixels[i])[1] - 1 + row_offset );
    }
    add_pixels_to_display_buffer(x, y, fontchar->n_pixels, color);
}
