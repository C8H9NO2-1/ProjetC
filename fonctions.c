#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define OPCODE_R 51

#define FUNCT7_SUB 32

void remplace(char *chaine) {
    int i = 0;
    while (chaine[i] != '#' && chaine[i] != '\n' && chaine[i] != '\0') {
        if (chaine[i] == ',' || chaine[i] == '(' || chaine[i] == ')') {
            chaine[i] = ' ';
        }
        i++;
    }
    chaine[i] = '\0';
}

char* recupereNomInstruction(char *instruction) {
    int i = 0;
    while (instruction[i] != ' ' && instruction[i] != '\0') {
        i++;
    }

    char *nom = malloc((i + 1) * sizeof(char));
    for (int j = 0; j < i; j++) {
        nom[j] = instruction[j];
    }
    nom[i] = '\0';

    return nom;
}

int charVersEntier(char *chaine) {
    int i = 0;
    int res = 0;

    while (chaine[i] != '\0') {
        res = 10 * res + (chaine[i] - '0');
        i++;
    }
    return res;
}

int registreVersEntier(char *registre, char **listeRegistre) {
    int resultat = -1;

    if (registre[0] == 'x') {
        char *numeroRegistre = malloc(3 * sizeof(char));
        for (int i = 0; i < 2; i++) {
            numeroRegistre[i] = registre[i + 1];
        }
        numeroRegistre[2] = '\0';
        resultat = charVersEntier(numeroRegistre);
    } else {
        int i = 0;
        bool trouve = false;
        while(i < 32 && !trouve) {
            if (!strcmp(listeRegistre[i], registre)) {
                trouve = true;
            } else {
                i++;
            }
        }
        resultat = i;
    }

    return resultat;
}

uint32_t formatR(char *instruction, char** listeRegistre) {
    uint32_t binaire = 0;
    
    // On récupère les trois registres de l'instruction
    int i = 0;
    int j = 0;
    char rd[5];
    char rs1[5];
    char rs2[5];

    // On passe le nom de l'instruction
    while (instruction[i] != ' ') {
        i++;
    }
    while (instruction[i] == ' ') {
        i++;
    }

    while (instruction[i] != ' ') {
        rd[j] = instruction[i];
        i++;
        j++;
    }
    while (instruction[i] == ' ') {
        i++;
    }
    rd[j] = '\0';

    j = 0;
    while (instruction[i] != ' ') {
        rs1[j] = instruction[i];
        i++;
        j++;
    }
    while (instruction[i] == ' ') {
        i++;
    }
    rs1[j] = '\0';

    j = 0;
    while (instruction[i] != '\0') {
        rs2[j] = instruction[i];
        i++;
        j++;
    }
    rs2[j] = '\0';

    // On écrit funct7
    char *nomInstruction = recupereNomInstruction(instruction);
    if (!strcmp(nomInstruction, "sub")) {
        binaire |= FUNCT7_SUB;
    }

    // On écrit rs2
    binaire <<= 5;
    int rs2Value = registreVersEntier(rs2, listeRegistre);
    if (rs2Value >= 0 && rs2Value <= 31) {
        binaire |= rs2Value;
    }

    // On écrit rs1
    binaire <<= 5;
    int rs1Value = registreVersEntier(rs1, listeRegistre);
    if (rs1Value >= 0 && rs1Value <= 31) {
        binaire |= rs1Value;
    }

    // On écrit funct3
        // Il n'y a rien à écrire, il faut juste décaler de 3 bits
    binaire <<= 3;

    // On écrit rd
    binaire <<= 5;
    int rdValue = registreVersEntier(rd, listeRegistre);
    if (rdValue >= 0 && rdValue <= 31) {
        binaire |= rdValue;
    }

    // On écrit l'opcode
    binaire <<= 7;
    binaire |= OPCODE_R;

    return binaire;
}

