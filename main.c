#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "fonctions.h"

#define TAILLE 100

//! Commande pour les tests: ./riscv-assembler tests/add-simple.s tests/add-simple.hex
// On peut aussi mettre des guiellemets autour des arguments pour les chemins avec des espaces

int main(int argc, char **argv)
{
    /* ./riscv-assembler <ASSEMBLER INPUT> <HEX OUTPUT> */
    if(argc != 3) {
        printf("usage: ./riscv-assembler <ASSEMBLER INPUT> <HEX OUTPUT>\n");
        return 1;
    }

    char *asm_input_file = argv[1];
    char *hex_output_file = argv[2];

    FILE* entree = fopen(asm_input_file, "r");
    FILE* sortie = fopen(hex_output_file, "w");

    char* listeRegistre[32] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

    char *ligne = NULL;
    size_t tailleLigne = 0;
    ssize_t characters = 0;
    // ligne = (char *) malloc(tailleLigne * sizeof(char));

    char *nomInstruction = NULL;
    uint32_t binaire = 0;

    while ((characters = getline(&ligne, &tailleLigne ,entree)) > 0) {
        
        if (ligne[0] == '#' || characters == 1) {
            continue;
        }

        remplace(ligne);

        nomInstruction = recupereNomInstruction(ligne);
        printf("Nom instruction: %s \n", nomInstruction);

        if (!(strcmp(nomInstruction, "add")) || !(strcmp(nomInstruction, "sub"))) {
            binaire = formatR(ligne, listeRegistre);
            // binaire = 51;
            fprintf(sortie, "%08x", binaire);
        }
        printf("Binaire: %08x \n", binaire);

        printf("You typed: '%s' \n", ligne);
    }

    free(ligne);

    fclose(entree);
    fclose(sortie);

    return 0;
}