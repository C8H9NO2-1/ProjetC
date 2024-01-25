#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "memoire.h"
#include "controle.h"

#define OPCODE_MASK 0x7F

#define FUNCT3_MASK 0x7000
#define FUNCT7_MASK 0xFE000000

#define RD_MASK 0xF80
#define RS1_MASK 0xF8000
#define RS2_MASK 0x1F00000

#define IMM_I_MASK 0xFFF00000
#define IMM_SD_MASK_1 0xF80
#define IMM_SD_MASK_2 0xFE000000
#define IMM_B_MASK_1 0xF00
#define IMM_B_MASK_2 0x7E000000
#define IMM_B_MASK_3 0x80
#define IMM_B_MASK_4 0x80000000
#define IMM_JAL_MASK_1 0x7FE00000
#define IMM_JAL_MASK_2 0x100000
#define IMM_JAL_MASK_3 0xFF000
#define IMM_JAL_MASK_4 0x80000000

#define OPCODE_R 0x33
#define OPCODE_ADDI 0x13
#define OPCODE_LD 0x3
#define OPCODE_SD 0x23
#define OPCODE_B 0x63
#define OPCODE_JAL 0x6F

#define FUNCT3_BEQ 0x0
#define FUNCT3_BNE 0x1
#define FUNCT3_BLT 0x4
#define FUNCT3_BGE 0x5

#define FUNCT7_ADD 0x0
#define FUNCT7_SUB 0x20


#define PREMIERS_32_BITS 0xFFFFFFFF00000000
#define DERNIERS_32_BITS 0xFFFFFFFF

void lireInstructions(uint8_t memoire[], char *fichier) {
    FILE* entree = fopen(fichier, "r");

    uint32_t *instruction = malloc(sizeof(uint32_t));

    int adresseActuelle = 0;

    // On parcourt le fichier en lisant chaque instruction
    while (fscanf(entree, "%08x", instruction) != EOF) {

        // On écrit l'instruction courante dans la mémoire sous forme de mots de 32 bits
        ecrire32bits(memoire, adresseActuelle, *instruction);

        adresseActuelle += 4;
    }

    printf("\n");

    free(instruction);

    fclose(entree);

}

// Cette fonction est un noeud de notre programme car elle exécute la bonne fonction selon l'opcode de l'instruction
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

    // Pour les nombres négatifs, on fait nous même l'extension de signe
    if (imm & 0b100000000000) {
        imm |= 0b1111100000000000;
    }

    // Si on essaie d'écrire dans le registre zero, on ne fait rien
    if (rd != 0) {
        registres[rd] = registres[rs1] + imm;
    }

    return 0;
}

int decodeExecuteLd(uint32_t instruction, int64_t registres[], uint8_t memoire[]) {
    int rd = (instruction & RD_MASK) >> 7;
    int rs1 = (instruction & RS1_MASK) >> 15;
    int16_t imm = (instruction & IMM_I_MASK) >> 20;

    // Extension de signe pour les nombres négatifs
    if (imm & 0b100000000000) {
        imm |= 0b1111100000000000;
    }

    // On récupère des données sur 64 bits si le registre de destination n'est pas zero
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

    // Extension de signe pour les nombres négatifs
    if (imm & 0b100000000000) {
        imm |= 0b1111100000000000;
    }

    ecrire64bits(memoire, registres[rs1] + imm, registres[rs2]);

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

    // Extension de signe pour les nombres négatifs
    if (imm & 0b1000000000000) {
        imm |= 0b1111000000000000;
    }

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

    // Extension de signe pour les nombres négatifs
    if (imm & 0b100000000000000000000) {
        imm |= 0b11111111111100000000000000000000;
    }

    if (rd != 0) {
        registres[rd] = *pc + 4;
    }
    *pc += imm;

    return 0;
}