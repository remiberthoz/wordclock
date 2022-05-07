#pragma once

namespace USB_USART {

    void init(void);
    void send_char(char c);
    char read_char();
}
