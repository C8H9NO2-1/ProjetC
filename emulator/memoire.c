#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "memoire.h"

#define MAX_ADRESSE 16383

uint32_t lire32bits(uint8_t memoire[], uint32_t adresse) {
    uint32_t resultat = 0;

    if (adresse <= MAX_ADRESSE - 4) {    
        resultat = memoire[adresse];
        for (int i = 1; i < 4; i++) {
            resultat |= (memoire[adresse + i] << (8 * i));
        }
    }

    return resultat;
}

void ecrire32bits(uint8_t memoire[], uint32_t adresse, uint32_t x) {
    if (adresse <= MAX_ADRESSE - 4) {    
        memoire[adresse] = (x & 0xFF);
        memoire[adresse + 1] = (x & 0xFF00) >> 8;
        memoire[adresse + 2] = (x & 0xFF0000) >> 16;
        memoire[adresse + 3] = (x & 0xFF000000) >> 24;
    }
}

int64_t lire64bits(uint8_t memoire[], uint32_t adresse) {
    int64_t resultat = 0;
    
    
    if (adresse <= MAX_ADRESSE - 8) {    
        resultat = memoire[adresse];
        printf("\n");

        int64_t temp = 0;

        for (int i = 1; i < 8; i++) {
            temp = memoire[adresse + i];
            resultat |= (temp << (8 * i));
        }
    }

    return resultat;
}

void ecrire64bits(uint8_t memoire[], uint32_t adresse, int64_t x) {
    if (adresse <= MAX_ADRESSE - 8) {    
        memoire[adresse] = (x & 0xFF);
        memoire[adresse + 1] = (x & 0xFF00) >> 8;
        memoire[adresse + 2] = (x & 0xFF0000) >> 16;
        memoire[adresse + 3] = (x & 0xFF000000) >> 24;
        memoire[adresse + 4] = (x & 0xFF00000000) >> 32;
        memoire[adresse + 5] = (x & 0xFF0000000000) >> 40;
        memoire[adresse + 6] = (x & 0xFF000000000000) >> 48;
        memoire[adresse + 7] = (x & 0xFF00000000000000) >> 56;
    }
}
