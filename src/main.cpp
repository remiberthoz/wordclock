#include "Behaviour/behaviourmanager.h"
#include "Display/display.h"
#include "Peripherals/RealTimeClock/rtc.h"
#include "Peripherals/EventKeys/eventkeys.h"
#include "millis.h"
#include "Verbose/verbose.h"
#include "config.h"

#include <avr/interrupt.h>
#include <time.h>
#include <util/delay.h>
#include <util/eu_dst.h>


/**
 * Executes the run() method of a BEHAVIOUR until it returns false or the user quits.
 */
static void exhaust_behaviour(Behaviour*const behaviour) {

    while (1) {

        unsigned long start = millis();

        tm timeinfo = RealTimeClock::fetch_time();
        bool r = behaviour->run(&timeinfo);
        if (!r)
            return;

        EventKeys::Event pending_event{};

        while (millis() - start <= 500) {
            EventKeys::fetch();
            pending_event = EventKeys::get_pending();
            if (pending_event != EventKeys::Event::NONE)
                break;
        }

        switch (pending_event) {

            case EventKeys::Event::NEXT:
                printf_warn("Handling NEXT\n");
                behaviour->next(&timeinfo);
                break;

            case EventKeys::Event::PREV:
                printf_warn("Handling PREV\n");
                behaviour->prev(&timeinfo);
                break;

            case EventKeys::Event::VALIDATE:
                printf_warn("Handling VALIDATE\n");
                behaviour->validate(&timeinfo);
                break;

            case EventKeys::Event::VALIDATE_LONG:
                printf_warn("Handling VALIDATE_LONG (QUIT)\n");
                return;

            default:
                break;
        }
    }
}


void init_arduino_board() {

    // Setup clock control
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wold-style-cast"
    _PROTECTED_WRITE(CLKCTRL_MCLKCTRLB, 0);
    #pragma GCC diagnostic pop

    // Setup USB (for stdio.h in Verbose/verbose.h)
    printf_init();

    // Set TCA0 in SPLIT MODE, we look at the LSB counting down from UINT8_MAX
    // down to zero. Activate the DIV64 prescaler, and the underflow interrupt.
    // This is used by the function millis().
    TCA0.SPLIT.CTRLD = TCA_SPLIT_ENABLE_bm;  // SPLIT MODE
    TCA0.SPLIT.LPER = UINT8_MAX;
    TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV64_gc | TCA_SPLIT_ENABLE_bm;  // TIMER ENABLE
    TCA0.SPLIT.INTCTRL = TCA_SPLIT_LUNF_bm;

    // PORTMUX.USARTROUTEA |= PORTMUX_USART3_NONE_gc;
}


void init_peripherals() {
    set_dst(eu_dst);  // Set timezone
    EventKeys::init();
    RealTimeClock::init();
    while (!Display::init_display()) {};
}


int main() {

    init_arduino_board();
    init_peripherals();
    printf_info("Done initializing\n");

    printf_info("Exhausting startup behaviour\n");
    exhaust_behaviour(BehaviourManager::get_selected_behaviour());
    BehaviourManager::select_next_behaviour();

    while(1) {
        printf_info("Running selected behaviour: %s\n", BehaviourManager::get_selected_behaviour()->behaviourName);
        exhaust_behaviour(BehaviourManager::get_selected_behaviour());
        BehaviourManager::select_next_behaviour();
    }
}
