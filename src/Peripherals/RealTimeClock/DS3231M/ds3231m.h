#pragma once
#include <time.h>

namespace RealTimeClock {

    namespace DS3231M {

        void init();
        tm fetch_time();
        bool set_time(tm* timeinfo);
    }
}
