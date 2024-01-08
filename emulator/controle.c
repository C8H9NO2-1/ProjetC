#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "memoire.h"
#include "controle.h"

#define OPCODE_MASK 0b1111111

#define FUNCT3_MASK 0b111000000000000
#define FUNCT7_MASK 0b11111110000000000000000000000000

#define RD_MASK 0b111110000000
#define RS1_MASK 0b11111000000000000000
#define RS2_MASK 0b1111100000000000000000000

#define IMM_I_MASK 0b11111111111100000000000000000000
#define IMM_SD_MASK_1 0b111110000000
#define IMM_SD_MASK_2 0b11111110000000000000000000000000
#define IMM_B_MASK_1 0b111100000000
#define IMM_B_MASK_2 0b1111110000000000000000000000000
#define IMM_B_MASK_3 0b10000000
#define IMM_B_MASK_4 0b10000000000000000000000000000000
#define IMM_JAL_MASK_1 0b1111111111000000000000000000000
#define IMM_JAL_MASK_2 0b100000000000000000000
#define IMM_JAL_MASK_3 0b11111111000000000000
#define IMM_JAL_MASK_4 0b10000000000000000000000000000000

#define OPCODE_R 0b0110011
#define OPCODE_ADDI 0b0010011
#define OPCODE_LD 0b0000011
#define OPCODE_SD 0b0100011
#define OPCODE_B 0b1100011
#define OPCODE_JAL 0b1101111

#define FUNCT3_BEQ 0b000
#define FUNCT3_BNE 0b001
#define FUNCT3_BLT 0b100
#define FUNCT3_BGE 0b101

#define FUNCT7_ADD 0b0000000
#define FUNCT7_SUB 0b0100000

#define PREMIERS_32_BITS 0b1111111111111111111111111111111100000000000000000000000000000000
#define DERNIERS_32_BITS 0b11111111111111111111111111111111

int lireInstructions(uint8_t memoire[], char *fichier) {
    FILE* entree = fopen(fichier, "r");

    uint32_t *instruction = malloc(sizeof(uint32_t));

    int adresseActuelle = 0;

    while (fscanf(entree, "%08x", instruction) != EOF) {

        printf("%08x\n", *instruction);

        // On charge l'instruction dans la mémoire par octet
        ecrire32bits(memoire, adresseActuelle, *instruction);
        // memoire[adresseActuelle] = (*instruction & 0b11111111);
        // memoire[adresseActuelle + 1] = (*instruction & 0b1111111100000000) >> 8;
        // memoire[adresseActuelle + 2] = (*instruction & 0b111111110000000000000000) >> 16;
        // memoire[adresseActuelle + 3] = (*instruction & 0b11111111000000000000000000000000) >> 24;

        adresseActuelle += 4;
    }

    printf("\n");

    free(instruction);

    fclose(entree);

    return adresseActuelle;
}

// uint32_t lireInstructions(uint32_t memoire[], char *fichier) {
//     FILE* entree = fopen(fichier, "r");

//     uint32_t *instruction = malloc(sizeof(uint32_t));

//     uint32_t adresseActuelle = 0;

//     while (fscanf(entree, "%08x", instruction) != EOF) {

//         printf("%08x\n", *instruction);

//         // On charge l'instruction dans la mémoire par mot de 32 bits
//         memoire[adresseActuelle] = *instruction;

//         adresseActuelle++;
//     }

//     printf("\n");

//     free(instruction);

//     fclose(entree);

//     return adresseActuelle;
// }

int decodeExecuteInstruction(uint32_t instruction, int64_t registres[], uint32_t *pc, uint8_t memoire[]) {
    int opcode = instruction & OPCODE_MASK;

    switch (opcode) {
        case OPCODE_R:
            decodeExecuteR(instruction, registres);
            break;
        case OPCODE_ADDI:
            decodeExecuteAddi(instruction, registres);
            break;
        case OPCODE_LD:
            decodeExecuteLd(instruction, registres, memoire);
            break;
        case OPCODE_SD:
            decodeExecuteSd(instruction, registres, memoire);
            break;
        case OPCODE_B:
            decodeExecuteB(instruction, registres, pc);
            break;
        case OPCODE_JAL:
            decodeExecuteJal(instruction, registres, pc);
            break;
        default:
            printf("OPCODE inconnu\n");
            break;
    }

    return 0;
}

int decodeExecuteR(uint32_t instruction, int64_t registres[]) {
    int funct7 = (instruction & FUNCT7_MASK) >> 25;
    int rd = (instruction & RD_MASK) >> 7;
    int rs1 = (instruction & RS1_MASK) >> 15;
    int rs2 = (instruction & RS2_MASK) >> 20;

    switch (funct7) {
        case FUNCT7_ADD:
            if (rd != 0) {
                registres[rd] = registres[rs1] + registres[rs2];
            }
            break;
        case FUNCT7_SUB:
            if (rd != 0) {
                registres[rd] = registres[rs1] - registres[rs2];
            }
            break;
        default:
            printf("FUNCT7 inconnu\n");
            break;
    }

    return 0;
}

int decodeExecuteAddi(uint32_t instruction, int64_t registres[]) {
    int rd = (instruction & RD_MASK) >> 7;
    int rs1 = (instruction & RS1_MASK) >> 15;
    int16_t imm = (instruction & IMM_I_MASK) >> 20;

    if (imm & 0b100000000000) {
        imm |= 0b1111100000000000;
    }

    if (rd != 0) {
        registres[rd] = registres[rs1] + imm;
    }

    return 0;
}

int decodeExecuteLd(uint32_t instruction, int64_t registres[], uint8_t memoire[]) {
    int rd = (instruction & RD_MASK) >> 7;
    int rs1 = (instruction & RS1_MASK) >> 15;
    int16_t imm = (instruction & IMM_I_MASK) >> 20;

    if (imm & 0b100000000000) {
        imm |= 0b1111100000000000;
    }

    // On récupère des données sur 64 bits
    if (rd != 0) {
        registres[rd] = lire64bits(memoire, registres[rs1] + imm);
    }

    return 0;
}

int decodeExecuteSd(uint32_t instruction, int64_t registres[], uint8_t memoire[]) {
    int rs1 = (instruction & RS1_MASK) >> 15;
    int rs2 = (instruction & RS2_MASK) >> 20;
    int16_t imm = (instruction & IMM_SD_MASK_1) >> 7;
    imm |= ((instruction & IMM_SD_MASK_2) >> 20);

    if (imm & 0b100000000000) {
        imm |= 0b1111100000000000;
    }

    ecrire64bits(memoire, registres[rs1] + imm, registres[rs2]);
    // memoire[registres[rs1] + imm + 1] = (registres[rs2] & PREMIERS_32_BITS) >> 32;
    // memoire[registres[rs1] + imm] = registres[rs2] & DERNIERS_32_BITS;

    return 0;
}

int decodeExecuteB(uint32_t instruction, int64_t registres[], uint32_t *pc) {
    int funct3 = (instruction & FUNCT3_MASK) >> 12;
    int rs1 = (instruction & RS1_MASK) >> 15;
    int rs2 = (instruction & RS2_MASK) >> 20;
    int16_t imm = (instruction & IMM_B_MASK_1) >> 7;
    imm |= ((instruction & IMM_B_MASK_2) >> 20);
    imm |= ((instruction & IMM_B_MASK_3) << 4);
    imm |= ((instruction & IMM_B_MASK_4) >> 19);

    if (imm & 0b1000000000000) {
        imm |= 0b1111000000000000;
    }

    printf("imm = %d\n", imm);

    switch (funct3) {
        case FUNCT3_BEQ:
            if (registres[rs1] == registres[rs2]) {
                *pc += imm;
            }
            break;
        case FUNCT3_BNE:
            if (registres[rs1] != registres[rs2]) {
                *pc += imm;
            }
            break;
        case FUNCT3_BLT:
            if (registres[rs1] < registres[rs2]) {
                *pc += imm;
            }
            break;
        case FUNCT3_BGE:
            if (registres[rs1] >= registres[rs2]) {
                *pc += imm;
            }
            break;
        default:
            break;
    }

    return 0;
}

int decodeExecuteJal(uint32_t instruction, int64_t registres[], uint32_t *pc) {
    int rd = (instruction & RD_MASK) >> 7;
    int32_t imm = (instruction & IMM_JAL_MASK_1) >> 20;
    imm |= ((instruction & IMM_JAL_MASK_2) >> 9);
    imm |= (instruction & IMM_JAL_MASK_3);
    imm |= ((instruction & IMM_JAL_MASK_4) >> 11);

    if (imm & 0b100000000000000000000) {
        imm |= 0b11111111111100000000000000000000;
    }

    if (rd != 0) {
        registres[rd] = *pc + 4;
    }
    *pc += imm;

    return 0;
}