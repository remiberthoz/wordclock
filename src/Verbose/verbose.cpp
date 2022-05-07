#include "verbose.h"
#include "../Protocols/USB_USART/usart.h"
#include "../config.h"


static int put(char c, FILE*) {
    if constexpr(_VERB) {
        USB_USART::send_char(c);
    }
    return 0;
}


static int get(FILE*) {
    if constexpr(_VERB) {
        return USB_USART::read_char();
    }
    return 0;
}


void printf_init() {
    USB_USART::init();
    fdevopen(&put, &get);
}
