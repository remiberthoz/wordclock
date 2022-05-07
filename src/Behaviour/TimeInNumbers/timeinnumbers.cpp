#include "../../Display/display.h"
#include "../../Layout/dotimatrix5.h"
#include "../../Peripherals/RealTimeClock/rtc.h"
#include "../../Verbose/verbose.h"
#include "timeinnumbers.h"

#include <time.h>

static uint8_t last_minute = 61;
static const Layout::fontchar_t* fontchars_hour[2];
static const Layout::fontchar_t* fontchars_min[2];


static void activate_fontchars_for_time(const tm* timeinfo) {

    int8_t disp_hour = timeinfo->tm_hour;
    int8_t disp_hour_tens = disp_hour / 10;
    int8_t disp_hour_ones = disp_hour % 10;
    fontchars_hour[0] = Layout::digit_to_fontchar<Layout::DOTIMATRIX5>(disp_hour_ones);
    fontchars_hour[1] = Layout::digit_to_fontchar<Layout::DOTIMATRIX5>(disp_hour_tens);

    int8_t disp_min = timeinfo->tm_min;
    int8_t disp_min_tens = disp_min / 10;
    int8_t disp_min_ones = disp_min % 10;
    fontchars_min[0] = Layout::digit_to_fontchar<Layout::DOTIMATRIX5>(disp_min_ones);
    fontchars_min[1] = Layout::digit_to_fontchar<Layout::DOTIMATRIX5>(disp_min_tens);
}


bool TimeInNumbersBehaviour::run(tm* timeinfo) {

    printf_debug("Calling TimeInNumbersBehaviour\n");

    if (timeinfo->tm_min == last_minute)
        return true;

    printf_info("Updating display from WordClockBehaviour\n");
    Display::clear_display_buffer();

    activate_fontchars_for_time(timeinfo);
    Display::add_fontchar_to_display_buffer(fontchars_hour[0], Display::RED, 9, 0);
    Display::add_fontchar_to_display_buffer(fontchars_hour[1], Display::RED, 2, 0);
    Display::add_fontchar_to_display_buffer(fontchars_min[0], Display::BLUE, 9, 9);
    Display::add_fontchar_to_display_buffer(fontchars_min[1], Display::BLUE, 2, 9);

    Display::apply_display_buffer();

    last_minute = static_cast<uint8_t> (timeinfo->tm_min);
    return true;
}


void TimeInNumbersBehaviour::prev(tm* timeinfo) {

    timeinfo->tm_sec = 0;
    timeinfo->tm_min--;
    if (timeinfo->tm_min >= 60) {
        timeinfo->tm_min = 0;
        timeinfo->tm_hour++;
    } else if (timeinfo->tm_min < 0) {
        timeinfo->tm_min = 59;
        timeinfo->tm_hour--;
    }

    RealTimeClock::set_time(timeinfo);
}

void TimeInNumbersBehaviour::next(tm* timeinfo) {

    timeinfo->tm_sec = 0;
    timeinfo->tm_min++;
    if (timeinfo->tm_min >= 60) {
        timeinfo->tm_min = 0;
        timeinfo->tm_hour++;
    } else if (timeinfo->tm_min < 0) {
        timeinfo->tm_min = 59;
        timeinfo->tm_hour--;
    }

    RealTimeClock::set_time(timeinfo);
}
