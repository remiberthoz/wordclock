#pragma once
#include <time.h>

namespace RealTimeClock {

    void init();
    tm fetch_time();
    bool set_time(tm* timeinfo);
}
