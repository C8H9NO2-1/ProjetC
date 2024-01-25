#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "memoire.h"
#include "controle.h"

//! Commande pour les tests: ./riscv-emulator tests/add-simple.hex tests/add-simple.state

//TODO Penser à vérifier les sauts dans la mémoire (ceux liés à PC), notamment pour les sauts négatifs

int main(int argc, char **argv)
{
    /* ./riscv-emulator <HEX INPUT> <EMULATION OUTPUT> */
    if(argc != 3) {
        printf("Usage: ./riscv-emulator <HEX INPUT> <EMULATION OUTPUT>\n");
        printf("error: invalid command\n");
        return 1;
    }

    char *hex_input_file = argv[1];
    char *emu_output_file = argv[2];

    //! Phase d'initialisation du programme

    // On défini une mémoir en octets
    uint8_t memoire[16384] = {0};

    // On lit l'ensemble des instructions du programme en assembleur
    lireInstructions(memoire, hex_input_file);

    // On assigne les registres à 0 sauf sp qui est à 16384
    int64_t registres[32] = {0};
    registres[2] = 16384; // On initialise sp à 16384
    uint32_t pc = 0; // On fait attention car on travaille avec une mémoire sur 32 bits


    //! Phase d'exécution du programme

    while (lire32bits(memoire, pc) != 0) {
        uint32_t instruction = lire32bits(memoire, pc);

        if (decodeExecuteInstruction(instruction, registres, &pc, memoire) != 0) {
            printf("Erreur lors de l'éxécution de l'instruction à l'adresse: %d", pc);
            return 1;
        }

        pc += 4;
    }

    //! Phase de sauvegarde de l'état de l'émulateur
    FILE *sortie = fopen(emu_output_file, "w");
    for (int i = 0; i < 32; i++) {
        fprintf(sortie, "x%d: %lld\n", i, registres[i]);
    }

    fclose(sortie);

    return 0;
}
