#pragma once
#include <avr/pgmspace.h>

typedef struct {
    uint8_t row;
    uint8_t start;
    uint8_t length;
} word_t;

namespace WORDS {
    constexpr uint8_t N_WORDS = 72;

    constexpr word_t PROGMEM A{7, 14, 1};
    constexpr word_t PROGMEM AIME{8, 5, 4};
    constexpr word_t PROGMEM ANNEE{6, 10, 5};
    constexpr word_t PROGMEM ANNIVERSAIRE{3, 4, 12};
    constexpr word_t PROGMEM BON{1, 9, 3};
    constexpr word_t PROGMEM BONJOUR{0, 0, 7};
    constexpr word_t PROGMEM BONNE{5, 4, 5};
    constexpr word_t PROGMEM BONSOIR{1, 9, 7};
    constexpr word_t PROGMEM DE1{10, 4, 2};
    constexpr word_t PROGMEM DE2{13, 5, 2};
    constexpr word_t PROGMEM FERIE{2, 11, 5};
    constexpr word_t PROGMEM FETE{5, 11, 4};
    constexpr word_t PROGMEM FETES{5, 11, 5};
    constexpr word_t PROGMEM FRANCE{12, 10, 6};
    constexpr word_t PROGMEM HORLOGE{0, 9, 7};
    constexpr word_t PROGMEM JE{0, 7, 2};
    constexpr word_t PROGMEM JOUR{15, 0, 4};
    constexpr word_t PROGMEM JOYEUSE{4, 2, 7};
    constexpr word_t PROGMEM JOYEUSES{4, 2, 8};
    constexpr word_t PROGMEM JOYEUX{1, 1, 6};
    constexpr word_t PROGMEM LA{11, 12, 2};
    constexpr word_t PROGMEM LISE{9, 8, 4};
    constexpr word_t PROGMEM MOTS{11, 0, 4};
    constexpr word_t PROGMEM NOEL{6, 6, 4};
    constexpr word_t PROGMEM NUIT{12, 1, 4};
    constexpr word_t PROGMEM PAR{12, 5, 3};
    constexpr word_t PROGMEM PART{12, 5, 4};
    constexpr word_t PROGMEM REMI{15, 11, 4};
    constexpr word_t PROGMEM T{8, 3, 1};
    constexpr word_t PROGMEM TEST{3, 0, 4};
    constexpr word_t PROGMEM VIVE{10, 12, 4};
    constexpr word_t PROGMEM WEEKEND{2, 4, 7};

    constexpr word_t PROGMEM HEART{15, 15, 1};

    constexpr word_t PROGMEM IL{4, 0, 2};
    constexpr word_t PROGMEM EST{5, 1, 3};
    constexpr word_t PROGMEM QUATRE{6, 0, 6};
    constexpr word_t PROGMEM HUIT{7, 0, 4};
    constexpr word_t PROGMEM TROIS{7, 3, 5};
    constexpr word_t PROGMEM SEPT{7, 7, 4};
    constexpr word_t PROGMEM SIX{7, 11, 3};
    constexpr word_t PROGMEM UNE{8, 0, 3};
    constexpr word_t PROGMEM MIDI{8, 9, 4};
    constexpr word_t PROGMEM DIX1{8, 13, 3};
    constexpr word_t PROGMEM NEUF{9, 0, 4};
    constexpr word_t PROGMEM DEUX{9, 4, 4};
    constexpr word_t PROGMEM CINQ1{9, 12, 4};
    constexpr word_t PROGMEM ONZE{10, 0, 4};
    constexpr word_t PROGMEM MINUIT{10, 6, 6};
    constexpr word_t PROGMEM HEURE{11, 6, 5};
    constexpr word_t PROGMEM HEURES{11, 6, 6};
    constexpr word_t PROGMEM MOINS{13, 0, 5};
    constexpr word_t PROGMEM LE{13, 7, 2};
    constexpr word_t PROGMEM ET{13, 8, 2};
    constexpr word_t PROGMEM DIX2{13, 11, 3};
    constexpr word_t PROGMEM DEMI{14, 1, 4};
    constexpr word_t PROGMEM DEMIE{14, 1, 5};
    constexpr word_t PROGMEM VINGT{14, 6, 5};
    constexpr word_t PROGMEM CINQ2{14, 12, 4};
    constexpr word_t PROGMEM QUART{15, 5, 5};
}
