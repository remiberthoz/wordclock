#include "behaviourmanager.h"

#include "BlinkOneAtATime/blinkoneatatime.h"
#include "HelloMessage/hellomessage.h"
#include "DateInNumbers/dateinnumbers.h"
#include "TimeInNumbers/timeinnumbers.h"
#include "WordClock/wordclock.h"


uint8_t selected_behaviour = 0;

BlinkOneAtATimeBehaviour blinkOneAtATimeBehaviour;
HelloMessageBehaviour helloMessageBehaviour;
TimeInNumbersBehaviour timeInNumbersBehaviour;
DateInNumbersBehaviour dateInNumbersBehaviour;
WordClockBehaviour wordClockBehaviour;


/**
 * Must match exactly the lenght of the array below.
 * Not larger, not shorter !!!
 */
constexpr uint8_t N_BEHAVIOURS = 5;

/**
 * Behaviour at index 0 is the one that shows up at startup,
 * behaviour at index 1 is the one that shows next.
 */
Behaviour* behaviours[N_BEHAVIOURS] = {
    &helloMessageBehaviour,
    &wordClockBehaviour,
    &timeInNumbersBehaviour,
    &blinkOneAtATimeBehaviour,
    &dateInNumbersBehaviour,
};


Behaviour* BehaviourManager::get_selected_behaviour() {
    return behaviours[selected_behaviour];
}


void BehaviourManager::select_next_behaviour() {
    selected_behaviour++;
    if (selected_behaviour > N_BEHAVIOURS)
        selected_behaviour = 1;
}
