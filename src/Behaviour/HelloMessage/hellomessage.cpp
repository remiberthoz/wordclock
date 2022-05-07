#include "../../Layout/words.h"
#include "../../Display/display.h"
#include "../../Verbose/verbose.h"
#include "hellomessage.h"

#include <stdint.h>
#include <time.h>

static constexpr uint8_t N_WORDS = 6;
constexpr const word_t* message[N_WORDS] = {&WORDS::HORLOGE, &WORDS::A, &WORDS::MOTS, &WORDS::PAR, &WORDS::REMI, &WORDS::HEART};
static uint8_t n_already_active_words = 0;

static constexpr uint8_t N_LETTERS = 20;
static uint8_t n_already_active_letters = 0;
static uint8_t n_already_active_letters_in_current_word = 0;
static uint8_t already_active_letters_x[N_LETTERS];
static uint8_t already_active_letters_y[N_LETTERS];

static time_t last_time = 0;


static bool activate_next_letter() {

    word_t current_word;
    memcpy_P(&current_word, message[n_already_active_words], sizeof(word_t));
    if (n_already_active_letters_in_current_word == current_word.length) {
        n_already_active_words++;
        n_already_active_letters_in_current_word = 0;
        if (n_already_active_words == N_WORDS)
            return false;
    }
    memcpy_P(&current_word, message[n_already_active_words], sizeof(word_t));

    already_active_letters_x[n_already_active_letters] = static_cast<uint8_t> (current_word.start + n_already_active_letters_in_current_word);
    already_active_letters_y[n_already_active_letters] = current_word.row;

    n_already_active_letters_in_current_word++;
    n_already_active_letters++;
    return true;
}


bool HelloMessageBehaviour::run(tm* timeinfo) {

    printf_debug("Calling HelloMessageBehaviour\n");

    time_t now = mk_gmtime(timeinfo);
    if (now - last_time < 1)
        return true;

    bool has_next = activate_next_letter();
    last_time = now;

    printf_info("Updating display from HelloMessageBehaviour\n");
    Display::clear_display_buffer();
    Display::add_pixels_to_display_buffer(already_active_letters_x, already_active_letters_y, n_already_active_letters, Display::YELLOW);
    Display::apply_display_buffer();

    return has_next;
}
