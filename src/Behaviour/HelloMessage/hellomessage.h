#pragma once
#include "../behaviour.h"
#include <time.h>

class HelloMessageBehaviour : public Behaviour {

    public:
        const char*const behaviourName = "HelloMessage";
        bool run(tm* timeinfo) override;

};
