#pragma once
#include "../../Protocols/OneButton/onebutton.h"
#include "events.h"

namespace EventKeys {

    void init();
    void fetch();
    Event get_pending();
}
