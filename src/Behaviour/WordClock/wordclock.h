#pragma once
#include "../behaviour.h"
#include <time.h>

class WordClockBehaviour : public Behaviour {

    public:
        const char*const behaviourName = "WordClock";
        bool run(tm* timeinfo) override;

};
