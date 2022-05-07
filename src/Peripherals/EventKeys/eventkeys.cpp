#include "eventkeys.h"
#include "../../Verbose/verbose.h"

OneButton button_prev{&PORTB, 0, true, true};
OneButton button_quit{&PORTB, 1, true, true};
OneButton button_next{&PORTB, 2, true, true};

EventKeys::Event pending_event = EventKeys::Event::NONE;

static void set_event_prev() {
    printf_warn("Button prev pressed\n");
    pending_event = EventKeys::Event::PREV;
}
static void set_event_quit() {
    printf_warn("Button quit pressed\n");
    pending_event = EventKeys::Event::VALIDATE;
}
static void set_event_next() {
    printf_warn("Button next pressed\n");
    pending_event = EventKeys::Event::NEXT;
}
static void set_event_quit_long() {
    printf_warn("Button quit long pressed\n");
    pending_event = EventKeys::Event::VALIDATE_LONG;
}


void EventKeys::init() {

    button_prev.init();
    button_quit.init();
    button_next.init();

    pending_event = Event::NONE;

    button_prev.attachClick(set_event_prev);
    button_quit.attachClick(set_event_quit);
    button_next.attachClick(set_event_next);
    button_quit.attachLongPressStart(set_event_quit_long);
}

void EventKeys::fetch() {
    button_prev.tick();
    button_quit.tick();
    button_next.tick();
}

EventKeys::Event EventKeys::get_pending() {
    Event p = pending_event;
    pending_event = Event::NONE;
    return p;
}
