#pragma once
#include "../behaviour.h"
#include <time.h>

class BlinkOneAtATimeBehaviour : public Behaviour {

    public:
        const char*const behaviourName = "BlinkOneAtATime";
        bool run(tm* timeinfo) override;

};
