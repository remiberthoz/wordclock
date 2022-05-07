#pragma once
#include <time.h>

class Behaviour {

    public:
        const char*const behaviourName = 0;
        virtual bool run(tm* timeinfo) = 0;
        virtual void next(tm*) {};
        virtual void prev(tm*) {};
        virtual void validate(tm*) {};
        // virtual void preview();

};
