#pragma once
#include "../behaviour.h"

class DateInNumbersBehaviour : public Behaviour {

    public:
        const char*const behaviourName = "DateInNumbers";
        bool run(tm* timeinfo) override;
        void next(tm* timeinfo) override;
        void prev(tm* timeinfo) override;

};
