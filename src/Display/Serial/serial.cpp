#include "../../Verbose/verbose.h"
#include "serial.h"


bool Display::Serial::impl_init_display() {
    return true;
}

void Display::Serial::impl_apply_buffer(uint8_t buffer[Display::N_ROWS][Display::N_COLS][3]) {

    printf("DISPLAY: ================\n");
    for (uint8_t row = 0; row < Display::N_ROWS; row++) {

        printf("DISPLAY: ");
        for (uint8_t col = 0; col < Display::N_COLS; col++) {

            bool show = false;
            for (uint8_t chn = 0; chn < 3; chn++) {
                if (buffer[row][col][chn] > 0) {
                    show = true;
                }
            }
            printf(show ? "X" : "-");
        }
        printf("\n");
    }
}
