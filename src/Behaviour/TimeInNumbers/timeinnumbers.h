#pragma once
#include "../behaviour.h"

class TimeInNumbersBehaviour : public Behaviour {

    public:
        const char*const behaviourName = "TimeInNumbers";
        bool run(tm* timeinfo) override;
        void next(tm* timeinfo) override;
        void prev(tm* timeinfo) override;

};
