#include "../../Display/display.h"
#include "../../Verbose/verbose.h"
#include "blinkoneatatime.h"


static time_t last_time = 0;
static uint8_t current_x = 0;
static uint8_t current_y = 0;
static uint8_t current_x0 = 0;
static uint8_t current_y0 = 0;
static uint8_t color_index = 0;
static color_t current_color;


static bool switch_to_next() {
    if (++current_x == 16) {
        current_x = 0;
        if (++current_y == 16)
            return false;
    }
    if (++color_index == 10) {
        color_index = 0;
    }
    switch (color_index) {
        case 0:
            current_color = Display::BLACK;
            break;
        case 1:
            current_color = Display::BLUE;
            break;
        case 2:
            current_color = Display::GREEN;
            break;
        case 3:
            current_color = Display::PINK;
            break;
        case 4:
            current_color = Display::PURPLE;
            break;
        case 5:
            current_color = Display::RED;
            break;
        case 6:
            current_color = Display::WHITE;
            break;
        case 7:
            current_color = Display::WWHITE;
            break;
        case 8:
            current_color = Display::YELLOW;
            break;
        case 9:
            current_color = Display::ORANGE;
            break;
        default:
            current_color = Display::BLACK;
    }
    return true;
}


bool BlinkOneAtATimeBehaviour::run(tm* timeinfo) {

    printf_debug("Calling BlinkOneAtATime\n");

    time_t now = mk_gmtime(timeinfo);
    // if (now - last_time < 1)
    //     return true;

    bool has_next = switch_to_next();
    last_time = now;

    printf_info("Updating display from BlinkOneAtATime\n");
    Display::clear_display_buffer();
    Display::add_pixels_to_display_buffer(&current_x0, &current_y0, 1, current_color);
    Display::add_pixels_to_display_buffer(&current_x, &current_y, 1, Display::RED);
    Display::apply_display_buffer();

    return has_next;
}
