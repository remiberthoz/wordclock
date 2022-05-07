#pragma once
#include "../display.h"
#include <stdint.h>

namespace Display {

    namespace CircuitV1 {

        bool impl_init_display();
        void impl_apply_buffer(uint8_t buffer[Display::N_ROWS][Display::N_COLS][3]);
    }
}
