// Copyright (c) 2018 Arduino SA.  All right reserved.

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include "usart.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#define USB_USART_BAUD_RATE(BAUD_RATE) (F_CPU * 64 / (16 * static_cast<float> (BAUD_RATE)) + 0.5f)


void USB_USART::init(void) {

    uint8_t oldSREG = SREG;
    cli();

    PORTMUX.USARTROUTEA = PORTMUX_USART3_ALT1_gc;  // Set PORTMUX for UART3 to ALT1 mode (pin B4 and B5)

    uint16_t the_baud = 6648;  // TODO: Change this magic number
    // constexpr uint16_t baud_rate = 9600;
    // uint8_t sigrow_val = SIGROW.OSC16ERR5V;
    // uint16_t baud_setting = (64 * 20000000) / (16 * baud_rate);  // (((8 * F_CPU) / baud_rate) + 1) / 2;
    // baud_setting += (baud_setting * sigrow_val) / 1024;
    USART3.BAUD = the_baud;

    USART3.CTRLC = 0x03;  // Asynchronous, 8 data bits, no parity bit, 1 stop bit
    USART3.CTRLB = USART_RXEN_bm | USART_TXEN_bm | USART_RXMODE_NORMAL_gc;  // Enable receiver and transmitter
    USART3.CTRLA = 0;  // Set Receive Complete Interrupt Enable bit

    PORTB.DIRCLR = PIN5_bm;  // RX as input
    PORTB.OUTSET = PIN5_bm;  // RX pull up
    PORTB.OUTSET = PIN4_bm;  // TX high
    PORTB.DIRSET = PIN4_bm;  // TX as output

    SREG = oldSREG;
    sei();
}


void USB_USART::send_char(char c) {
    while (!(USART3.STATUS & USART_DREIF_bm)) {};
    USART3.TXDATAL = static_cast<uint8_t> (c);
}


char USB_USART::read_char() {
    while (!(USART3.STATUS & USART_RXCIF_bm)) {};
    return static_cast<char> (USART3.RXDATAL);
}
