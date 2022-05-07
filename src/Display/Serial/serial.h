#pragma once
#include "../display.h"

namespace Display {

    namespace Serial {

        bool impl_init_display();
        void impl_apply_buffer(uint8_t buffer[Display::N_ROWS][Display::N_COLS][3]);
    }
}
