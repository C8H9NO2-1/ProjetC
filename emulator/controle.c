#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "controle.h"

int lireInstructions(uint8_t memoire[], char *fichier) {
    FILE* entree = fopen(fichier, "r");

    uint32_t *instruction = malloc(sizeof(uint32_t));

    int adresseActuelle = 0;

    while (fscanf(entree, "%08x", instruction) != EOF) {

        printf("%08x\n\n", *instruction);

        memoire[adresseActuelle] = (*instruction & 0b11111111);
        memoire[adresseActuelle + 1] = (*instruction & 0b1111111100000000) >> 8;
        memoire[adresseActuelle + 2] = (*instruction & 0b111111110000000000000000) >> 16;
        memoire[adresseActuelle + 3] = (*instruction & 0b11111111000000000000000000000000) >> 24;

        adresseActuelle += 4;
    }

    free(instruction);

    fclose(entree);

    return adresseActuelle;
}