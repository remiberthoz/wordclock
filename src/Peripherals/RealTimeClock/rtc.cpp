#include "rtc.h"
#include "../../config.h"
#include "DS3231M/ds3231m.h"

tm now{};

void RealTimeClock::init() {
    if constexpr(RTC_DS3231M)
        DS3231M::init();
}


tm RealTimeClock::fetch_time() {
    if constexpr(RTC_DS3231M)
        return DS3231M::fetch_time();
    now.tm_sec++;
    return now;
}


bool RealTimeClock::set_time(tm *timeinfo) {

    bool problem = false;

    if constexpr(RTC_DS3231M)
        problem |= DS3231M::set_time(timeinfo);

    now.tm_sec = timeinfo->tm_sec;
    now.tm_min = timeinfo->tm_min;
    now.tm_hour = timeinfo->tm_hour;
    now.tm_wday = timeinfo->tm_wday;
    now.tm_mday = timeinfo->tm_mday;
    now.tm_mon = timeinfo->tm_mon;
    now.tm_yday = timeinfo->tm_yday;
    now.tm_year = timeinfo->tm_year;
    now.tm_isdst = timeinfo->tm_isdst;

    return problem;
}
