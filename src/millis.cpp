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

#include <avr/interrupt.h>

constexpr uint32_t TIMER_MAX = 256;
constexpr uint32_t TIMER_CPU_DIV = 64;

/**
 * The timer interrup service routine (ISR) will increment the TIMER_millis by
 * INTERRUPT_MILLIS_INCREMENT when it is called. For the TIMER_millis to be close
 * to real time, INTERRUPT_MILLIS_INCREMENT must correspond to the (truncated) number
 * of real milliseconds elapsed between two ISR calls.
 *
 * Since INTERRUPT_MILLIS_INCREMENT is truncated, the TIMER_millis will accumulate
 * an error (delay on the real time) in the form of missed elapsed real microseconds.
 * This error is tracked by the ISR, which counts the missing microseconds in
 * TIMER_missing_micros.
 *
 * In the ISR, whenever TIMER_missing_micros goes over 1000 (1000 microseconds = 1 millisecond),
 * then TIMER_millis is incremented by one extra millisecond, and TIMER_missing_micros decremented
 * by 1000.
 *
 * This prevents TIMER_millis from accumulating more than 1 ms of error due to integer arithmetics.
 */
constexpr double F_TIMER = F_CPU / TIMER_CPU_DIV;
constexpr double TIMER_TICKS_PER_MICROSECOND = F_TIMER / 1000000L;

constexpr uint32_t MICROS_PER_TIMER_INTERRUPT = TIMER_MAX / TIMER_TICKS_PER_MICROSECOND;
constexpr uint16_t MICROS_PER_MILLIS = 1000;

constexpr uint32_t INTERRUPT_MILLIS_INCREMENT = MICROS_PER_TIMER_INTERRUPT / MICROS_PER_MILLIS;
constexpr uint16_t INTERRUPT_MISSING_MICROS_INCREMENT = MICROS_PER_TIMER_INTERRUPT % MICROS_PER_MILLIS;


static volatile uint32_t TIMER_millis = 0;
static volatile uint16_t TIMER_missing_micros = 0;

SIGNAL(TCA0_LUNF_vect) {
    // Clear interrupt flag
    TCA0.SPLIT.INTFLAGS = TCA_SPLIT_LUNF_bm;

    // Get volatiles locally
    uint32_t _millis = TIMER_millis;
    uint16_t _missing_micros = TIMER_missing_micros;

    // Increment millis and missing micros
    _millis += INTERRUPT_MILLIS_INCREMENT;
    _missing_micros += INTERRUPT_MISSING_MICROS_INCREMENT;

    // Check if missing micros accumulated to 1 millis
    if (_missing_micros >= MICROS_PER_MILLIS) {
        _millis += 1;
        _missing_micros -= MICROS_PER_MILLIS;
    }

    // Update volatiles
    TIMER_millis = _millis;
    TIMER_missing_micros = _missing_micros;
}

uint32_t millis() {
    uint32_t _millis;
    uint8_t oldSREG = SREG;

    // disable interrupts while we read TIMER_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to TIMER_millis)
    cli();
    _millis = TIMER_millis;
    SREG = oldSREG;

    return _millis;
}
