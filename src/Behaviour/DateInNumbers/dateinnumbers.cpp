#include "../../Display/display.h"
#include "../../Layout/dotimatrix3.h"
#include "../../Layout/dotimatrix5.h"
#include "../../Layout/font.h"
#include "../../Peripherals/RealTimeClock/rtc.h"
#include "../../Verbose/verbose.h"
#include "dateinnumbers.h"

#include <time.h>

static uint8_t last_minute = 61;
static const Layout::fontchar_t* fontchars_wday[3];
static const Layout::fontchar_t* fontchars_mday[2];
static const Layout::fontchar_t* fontchars_mon[2];


static void activate_fontchars_for_date(const tm* timeinfo) {

    int8_t disp_wday = static_cast<int8_t> (timeinfo->tm_wday);
    switch (disp_wday) {
        case 0:
            fontchars_wday[2] = &Layout::DOTIMATRIX5::L;
            fontchars_wday[1] = &Layout::DOTIMATRIX5::u;
            fontchars_wday[0] = &Layout::DOTIMATRIX5::n;
            break;
        case 1:
            fontchars_wday[2] = &Layout::DOTIMATRIX5::M;
            fontchars_wday[1] = &Layout::DOTIMATRIX5::a;
            fontchars_wday[0] = &Layout::DOTIMATRIX5::r;
            break;
        case 2:
            fontchars_wday[2] = &Layout::DOTIMATRIX5::M;
            fontchars_wday[1] = &Layout::DOTIMATRIX5::e;
            fontchars_wday[0] = &Layout::DOTIMATRIX5::r;
            break;
        case 3:
            fontchars_wday[2] = &Layout::DOTIMATRIX5::J;
            fontchars_wday[1] = &Layout::DOTIMATRIX5::e;
            fontchars_wday[0] = &Layout::DOTIMATRIX5::u;
            break;
        case 4:
            fontchars_wday[2] = &Layout::DOTIMATRIX5::V;
            fontchars_wday[1] = &Layout::DOTIMATRIX5::e;
            fontchars_wday[0] = &Layout::DOTIMATRIX5::n;
            break;
        case 5:
            fontchars_wday[2] = &Layout::DOTIMATRIX5::S;
            fontchars_wday[1] = &Layout::DOTIMATRIX5::a;
            fontchars_wday[0] = &Layout::DOTIMATRIX5::m;
            break;
        case 6:
            fontchars_wday[2] = &Layout::DOTIMATRIX5::D;
            fontchars_wday[1] = &Layout::DOTIMATRIX5::i;
            fontchars_wday[0] = &Layout::DOTIMATRIX5::m;
            break;
    }

    int8_t disp_mday = timeinfo->tm_mday;
    int8_t disp_mday_tens = disp_mday / 10;
    int8_t disp_mday_ones = disp_mday % 10;
    fontchars_mday[0] = Layout::digit_to_fontchar<Layout::DOTIMATRIX3>(disp_mday_ones);
    fontchars_mday[1] = Layout::digit_to_fontchar<Layout::DOTIMATRIX3>(disp_mday_tens);

    int8_t disp_mon = timeinfo->tm_mon;
    disp_mon++;
    int8_t disp_mon_tens = disp_mon / 10;
    int8_t disp_mon_ones = disp_mon % 10;
    fontchars_mon[0] = Layout::digit_to_fontchar<Layout::DOTIMATRIX3>(disp_mon_ones);
    fontchars_mon[1] = Layout::digit_to_fontchar<Layout::DOTIMATRIX3>(disp_mon_tens);
}


bool DateInNumbersBehaviour::run(tm* timeinfo) {

    printf_debug("Calling TimeInNumbersBehaviour\n");

    if (timeinfo->tm_min == last_minute)
        return true;

    printf_info("Updating display from WordClockBehaviour\n");
    Display::clear_display_buffer();

    activate_fontchars_for_date(timeinfo);
    Display::add_fontchar_to_display_buffer(fontchars_wday[0], Display::WHITE, 10, 0);
    Display::add_fontchar_to_display_buffer(fontchars_wday[1], Display::WHITE, 5, 0);
    Display::add_fontchar_to_display_buffer(fontchars_wday[2], Display::WHITE, 0, 0);
    Display::add_fontchar_to_display_buffer(fontchars_mday[0], Display::RED, 4, 9);
    Display::add_fontchar_to_display_buffer(fontchars_mday[1], Display::RED, 0, 9);
    Display::add_fontchar_to_display_buffer(fontchars_mon[0], Display::ORANGE, 12, 9);
    Display::add_fontchar_to_display_buffer(fontchars_mon[1], Display::ORANGE, 8, 9);

    Display::apply_display_buffer();

    last_minute = static_cast<uint8_t> (timeinfo->tm_min);
    return true;
}


void DateInNumbersBehaviour::prev(tm* timeinfo) {

    timeinfo->tm_mday--;
    if (timeinfo->tm_mday >= 32) {
        timeinfo->tm_mday = 0;
        timeinfo->tm_mon++;
    } else if (timeinfo->tm_mday < 0) {
        timeinfo->tm_mday = 31;
        timeinfo->tm_mon--;
    }

    RealTimeClock::set_time(timeinfo);
}

void DateInNumbersBehaviour::next(tm* timeinfo) {

    timeinfo->tm_mday++;
    if (timeinfo->tm_mday >= 32) {
        timeinfo->tm_mday = 0;
        timeinfo->tm_mon++;
    } else if (timeinfo->tm_mday < 0) {
        timeinfo->tm_mday = 31;
        timeinfo->tm_mon--;
    }

    RealTimeClock::set_time(timeinfo);
}
