#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "controle.h"

//! Commande pour les tests: ./riscv-emulator tests/add-simple.hex tests/add-simple.state

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

    uint8_t memoire[16384] = {0};

    int adresseFinInstructions = lireInstructions(memoire, hex_input_file);

    return 0;
}
