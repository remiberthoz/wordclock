#include "../../Protocols/I2C/i2cnx.h"
#include "../../Verbose/verbose.h"
#include "circuitv1.h"


#define eight(x) {x, x, x, x, x, x, x, x}
#define if_nack_return(x) if (!ack) { printf_warn("I2CNX: NACK\n"); return x; }

constexpr uint8_t BASE_3236A_ADDR = 0b01111000;

static constexpr uint8_t ROW_OFFSET = 1;
static constexpr uint8_t ROW_PER_BUS = 3;
static constexpr uint8_t COL_PER_ADR = 4;
static constexpr uint8_t CHN_PER_LED = 3; // RGB: 3 channel per led
static constexpr uint8_t N_BUS = 6;
static constexpr uint8_t N_ADR = 4;
static constexpr uint8_t N_BUS_CIRC = 6;  // TODO: This shoulc be equal to N_BUS, unless debuging/developping
static constexpr uint8_t N_ADR_CIRC = 4;  // TODO: This shoulc be equal to N_BUS, unless debuging/developping
static constexpr uint8_t PINS_PER_SUBBOARD = ROW_PER_BUS * COL_PER_ADR * CHN_PER_LED;

static I2CNX I2C8X_CIRCUITV1{N_BUS_CIRC, &PORTE, 3, &PORTD, 0, 3};

static constexpr uint8_t subboard_pin_map[ROW_PER_BUS][COL_PER_ADR][CHN_PER_LED] = {
    {{10, 11, 12}, { 7,  8,  9}, { 6,  5,  4}, { 3,  2,  1}},
    {{15, 14, 13}, {24, 23, 22}, {36, 35, 34}, {32, 31, 33}},
    {{18, 17, 16}, {21, 20, 19}, {27, 26, 25}, {30, 29, 28}}
};

static uint8_t circuit_buffer[N_ADR][PINS_PER_SUBBOARD][N_BUS];

static inline uint8_t merge_3236a_addr(uint8_t var_addr) {
    return static_cast<uint8_t> ( BASE_3236A_ADDR | (var_addr << 1) );
}

static inline uint8_t board_pin_from_row_col_chn(const uint8_t row, const uint8_t col, const uint8_t chn) {
    uint8_t subboard_row = static_cast<uint8_t> ((row + ROW_OFFSET) % ROW_PER_BUS);
    uint8_t subboard_col = static_cast<uint8_t> (col % COL_PER_ADR);
    return static_cast<uint8_t> (subboard_pin_map[subboard_row][3-subboard_col][chn] - 1);
}


static inline uint8_t board_bus_from_row_col(const uint8_t row, const uint8_t col) {
    int posx = (row + ROW_OFFSET) * Display::N_COLS + col;
    return static_cast<uint8_t> (posx / (Display::N_ROWS * ROW_PER_BUS));  // Valid cast since posx<=271, 271/(16*3)=5<255
}


static inline uint8_t board_adr_from_row_col(const uint8_t row, const uint8_t col) {
    int posy = col * Display::N_ROWS + row;
    return static_cast<uint8_t> (3 - (posy / (Display::N_COLS * COL_PER_ADR)) );  // Valid cast since posy<=255, 255/(16*4)=3<255
}


static inline uint8_t board_led_form_row_col(const uint8_t row, const uint8_t col) {
    // relx,rely are x,y coordinated of a LED on its bus,adr pair
    int8_t relx = static_cast<int8_t> (col - COL_PER_ADR * board_adr_from_row_col(row, col));
    int8_t rely = static_cast<int8_t> ((row + ROW_OFFSET) - ROW_PER_BUS * board_bus_from_row_col(row, col));
    return static_cast<uint8_t> (rely*COL_PER_ADR + relx);  // Valid cast since relx<=3 and rely<=2, rely*4+3=11<255
}


static void clear_circuit_buffer() {
    for (uint8_t adr = 0; adr < N_ADR; adr++) {
        for (uint8_t pin = 0; pin < PINS_PER_SUBBOARD; pin++) {
            for (uint8_t bus = 0; bus < N_BUS; bus++) {
                circuit_buffer[adr][pin][bus] = 0;
            }
        }
    }
}


static void update_circuit_buffer_from_display_buffer(uint8_t display_buffer[Display::N_ROWS][Display::N_COLS][3]) {

    for (uint8_t row = 0; row < Display::N_ROWS; row++) {
        for (uint8_t col = 0; col < Display::N_COLS; col++) {
            uint8_t bus = board_bus_from_row_col(row, col);
            uint8_t adr = board_adr_from_row_col(row, col);
            for (uint8_t chn = 0; chn < CHN_PER_LED; chn++) {
                uint8_t pin = board_pin_from_row_col_chn(row, col, chn);
                circuit_buffer[adr][pin][bus] = display_buffer[row][col][chn];
            }
        }
    }
}


bool Display::CircuitV1::impl_init_display() {

    printf_info("Initializing display for CircuitV1\n");
    PORTD.DIRSET = 0b10000000;  // SDB output
    PORTD.OUTSET = 0b10000000;  // SDB high
    I2C8X_CIRCUITV1.init();

    for (uint8_t adr = 0; adr < N_ADR_CIRC; adr++) {

        bool ack;

        printf_debug("Iterrating boards at address: %u\n", adr);
        ack = I2C8X_CIRCUITV1.start_transmit(merge_3236a_addr(adr), 0x00, false);
        if_nack_return(false);
    }

    for (uint8_t adr = 0; adr < N_ADR_CIRC; adr++) {

        bool ack;

        printf_debug("Writing to SHUTDOWN REGISTER\n");
        uint8_t shutdown_no[8] = eight(1);
        ack = I2C8X_CIRCUITV1.start_transmit(merge_3236a_addr(adr), 0x00, true);
        if_nack_return(false);
        ack = I2C8X_CIRCUITV1.transmit(shutdown_no, false);
        if_nack_return(false);

        printf_debug("Writing to LED_CONTROL REGISTER\n");
        uint8_t led_state_on[8] = eight(0b111);
        ack = I2C8X_CIRCUITV1.start_transmit(merge_3236a_addr(adr), 0x26, true);
        if_nack_return(false);

        for (uint8_t pin = 0; pin < PINS_PER_SUBBOARD-1; pin++) {
            ack = I2C8X_CIRCUITV1.transmit(led_state_on, true);
            if_nack_return(false);
        }
        ack = I2C8X_CIRCUITV1.transmit(led_state_on, false);
        if_nack_return(false);
    }

    return true;
}


void Display::CircuitV1::impl_apply_buffer(uint8_t display_buffer[Display::N_ROWS][Display::N_COLS][3]) {

    printf_info("Applying display buffer on CircuitV1\n");

    clear_circuit_buffer();
    update_circuit_buffer_from_display_buffer(display_buffer);

    for (uint8_t adr = 0; adr < N_ADR_CIRC; adr++) {

        bool ack;

        printf_debug("Writing to PWM_CONTROL REGISTER\n");
        ack = I2C8X_CIRCUITV1.start_transmit(merge_3236a_addr(adr), 0x01, true);
        if_nack_return();

        for (uint8_t pin = 0; pin < PINS_PER_SUBBOARD; pin++) {
            ack = I2C8X_CIRCUITV1.transmit(circuit_buffer[adr][pin], true);
            if_nack_return();
        }

        printf_debug("Writing to PWM_UPDATE REGISTER\n");
        uint8_t pwm_update[8] = eight(0);
        ack = I2C8X_CIRCUITV1.transmit(pwm_update, false);
        if_nack_return();
    }
}
