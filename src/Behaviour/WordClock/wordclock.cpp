#include "../../Display/display.h"
#include "../../Layout/words.h"
#include "../../Verbose/verbose.h"
#include "wordclock.h"


static const word_t* active_words[WORDS::N_WORDS];
static uint8_t n_active_words;
static uint8_t last_minute = 61;
static uint8_t lucky_love_count = 0;


static void activate_word_list(const word_t* word) {
    active_words[n_active_words++] = word;
}
template<typename T, typename... Args> static void activate_word_list(T firstword, Args... otherwords) {
    activate_word_list(firstword);
    activate_word_list(otherwords...);
}


static void activate_words_for_time(const tm* timeinfo) {

    if (timeinfo->tm_hour > 5 && timeinfo->tm_hour <= 10)
        activate_word_list(&WORDS::BONJOUR, &WORDS::BONSOIR);
    else if (timeinfo->tm_hour > 17 && timeinfo->tm_hour <= 20)
        activate_word_list(&WORDS::BONSOIR);

    activate_word_list(&WORDS::IL);
    activate_word_list(&WORDS::EST);

    uint8_t disp_hour = static_cast<uint8_t> (timeinfo->tm_hour);
    if (timeinfo->tm_min > 32)
        disp_hour = static_cast<uint8_t> (disp_hour + 1);

    if (disp_hour == 0 || disp_hour == 24)
        activate_word_list(&WORDS::MINUIT);
    else if (disp_hour == 12)
        activate_word_list(&WORDS::MIDI);
    else if (disp_hour == 1 || disp_hour == 13)
        activate_word_list(&WORDS::UNE);
    else if (disp_hour == 2 || disp_hour == 14)
        activate_word_list(&WORDS::DEUX);
    else if (disp_hour == 3 || disp_hour == 15)
        activate_word_list(&WORDS::TROIS);
    else if (disp_hour == 4 || disp_hour == 16)
        activate_word_list(&WORDS::QUATRE);
    else if (disp_hour == 5 || disp_hour == 17)
        activate_word_list(&WORDS::CINQ1);
    else if (disp_hour == 6 || disp_hour == 18)
        activate_word_list(&WORDS::SIX);
    else if (disp_hour == 7 || disp_hour == 19)
        activate_word_list(&WORDS::SEPT);
    else if (disp_hour == 8 || disp_hour == 20)
        activate_word_list(&WORDS::HUIT);
    else if (disp_hour == 9 || disp_hour == 21)
        activate_word_list(&WORDS::NEUF);
    else if (disp_hour == 10 || disp_hour == 22)
        activate_word_list(&WORDS::DIX1);
    else if (disp_hour == 11 || disp_hour == 23)
        activate_word_list(&WORDS::ONZE);

    if (disp_hour != 0 && disp_hour != 12 && disp_hour != 24) {
        if (disp_hour != 1 && disp_hour != 13)
            activate_word_list(&WORDS::HEURES);
        else
            activate_word_list(&WORDS::HEURE);
    }

    if (timeinfo->tm_min > 2 && timeinfo->tm_min <= 7)
        activate_word_list(&WORDS::CINQ2);
    else if (timeinfo->tm_min > 7 && timeinfo->tm_min <= 12)
        activate_word_list(&WORDS::DIX2);
    else if (timeinfo->tm_min > 12 && timeinfo->tm_min <= 17)
        activate_word_list(&WORDS::ET, &WORDS::QUART);
    else if (timeinfo->tm_min > 17 && timeinfo->tm_min <= 22)
        activate_word_list(&WORDS::VINGT);
    else if (timeinfo->tm_min > 22 && timeinfo->tm_min <= 27)
        activate_word_list(&WORDS::VINGT, &WORDS::CINQ2);
    else if (timeinfo->tm_min > 27 && timeinfo->tm_min <= 32) {
        if (disp_hour == 0 || disp_hour == 12 || disp_hour == 24)
            activate_word_list(&WORDS::ET, &WORDS::DEMI);
        else
            activate_word_list(&WORDS::ET, &WORDS::DEMIE);
    }
    else if (timeinfo->tm_min > 32 && timeinfo->tm_min <= 37)
        activate_word_list(&WORDS::MOINS, &WORDS::VINGT, &WORDS::CINQ2);
    else if (timeinfo->tm_min > 37 && timeinfo->tm_min <= 42)
        activate_word_list(&WORDS::MOINS, &WORDS::VINGT);
    else if (timeinfo->tm_min > 42 && timeinfo->tm_min <= 47)
        activate_word_list(&WORDS::MOINS, &WORDS::LE, &WORDS::QUART);
    else if (timeinfo->tm_min > 47 && timeinfo->tm_min <= 52)
        activate_word_list(&WORDS::MOINS, &WORDS::DIX2);
    else if (timeinfo->tm_min > 52 && timeinfo->tm_min <= 57)
        activate_word_list(&WORDS::MOINS, &WORDS::CINQ2);
}


static void activate_words_for_message(const tm* timeinfo) {

    if (timeinfo->tm_mon+1 == 3 && timeinfo->tm_mday == 18)
        activate_word_list(&WORDS::JOYEUX, &WORDS::ANNIVERSAIRE, &WORDS::LISE, &WORDS::DE1, &WORDS::LA, &WORDS::PART, &WORDS::DE2, &WORDS::REMI);
    else if (timeinfo->tm_mon+1 == 11 && timeinfo->tm_mday == 4)
        activate_word_list(&WORDS::JOYEUX, &WORDS::ANNIVERSAIRE, &WORDS::REMI);
    else if (timeinfo->tm_mon+1 == 12 && timeinfo->tm_mday == 24 && timeinfo->tm_hour > 19)
        activate_word_list(&WORDS::JOYEUX, &WORDS::NOEL);
    else if (timeinfo->tm_mon+1 == 12 && timeinfo->tm_mday == 25)
        activate_word_list(&WORDS::JOYEUX, &WORDS::NOEL);
    else if (timeinfo->tm_mon+1 == 7 && timeinfo->tm_mday == 14)
        activate_word_list(&WORDS::VIVE, &WORDS::LA, &WORDS::FRANCE);
    else if (timeinfo->tm_mon+1 == 1 && timeinfo->tm_mday == 1)
        activate_word_list(&WORDS::BONNE, &WORDS::ANNEE);
    else if (timeinfo->tm_mon+1 == 12 && timeinfo->tm_mday == 6)
        activate_word_list(&WORDS::JOYEUSES, &WORDS::FETES);
    else if (timeinfo->tm_mon+1 == 11 && timeinfo->tm_mday == 17)
        activate_word_list(&WORDS::JOYEUSE, &WORDS::FETE, &WORDS::LISE);

    else if (lucky_love_count > 0)
        activate_word_list(&WORDS::JE, &WORDS::T, &WORDS::AIME, &WORDS::LISE, &WORDS::HEART);
}


bool WordClockBehaviour::run(tm* timeinfo) {

    printf_debug("Calling WordClockBehaviour\n");

    if (timeinfo->tm_min == last_minute)
        return true;

    printf_info("Updating display from WordClockBehaviour\n");
    Display::clear_display_buffer();

    n_active_words = 0;
    activate_words_for_time(timeinfo);
    Display::add_words_to_display_buffer(active_words, n_active_words, Display::RED);

    n_active_words = 0;
    activate_words_for_message(timeinfo);
    Display::add_words_to_display_buffer(active_words, n_active_words, Display::PURPLE);

    Display::apply_display_buffer();

    last_minute = static_cast<uint8_t> (timeinfo->tm_min);
    return true;
}
