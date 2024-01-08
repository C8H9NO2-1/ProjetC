#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "memoire.h"

uint32_t lire32bits(uint8_t memoire[], uint32_t adresse) {
    uint32_t resultat = memoire[adresse];
    for (int i = 1; i < 4; i++) {
        resultat |= (memoire[adresse + i] << (8 * i));
    }

    return resultat;
}

void ecrire32bits(uint8_t memoire[], uint32_t adresse, uint32_t x) {
    memoire[adresse] = (x & 0b11111111);
    memoire[adresse + 1] = (x & 0b1111111100000000) >> 8;
    memoire[adresse + 2] = (x & 0b111111110000000000000000) >> 16;
    memoire[adresse + 3] = (x & 0b11111111000000000000000000000000) >> 24;
}

int64_t lire64bits(uint8_t memoire[], uint32_t adresse) {
    int64_t resultat = memoire[adresse];
    for (int i = 1; i < 8; i++) {
        resultat |= (memoire[adresse + i] << (8 * i));
    }

    return resultat;
}

void ecrire64bits(uint8_t memoire[], uint32_t adresse, int64_t x) {
    memoire[adresse] = (x & 0b11111111);
    memoire[adresse + 1] = (x & 0b1111111100000000) >> 8;
    memoire[adresse + 2] = (x & 0b111111110000000000000000) >> 16;
    memoire[adresse + 3] = (x & 0b11111111000000000000000000000000) >> 24;
    memoire[adresse + 4] = (x & 0b1111111100000000000000000000000000000000) >> 32;
    memoire[adresse + 5] = (x & 0b111111110000000000000000000000000000000000000000) >> 40;
    memoire[adresse + 6] = (x & 0b11111111000000000000000000000000000000000000000000000000) >> 48;
    memoire[adresse + 7] = (x & 0b1111111100000000000000000000000000000000000000000000000000000000) >> 56;
}