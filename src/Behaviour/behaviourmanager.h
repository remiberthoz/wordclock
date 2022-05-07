#pragma once
#include "behaviour.h"

class BehaviourManager {

    public:
        static Behaviour* get_selected_behaviour();
        static void select_next_behaviour();
};
