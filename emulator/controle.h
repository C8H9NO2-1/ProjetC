#ifndef __CONTROLE_H__
#define __CONTROLE_H__

int lireInstructions(uint8_t memoire[], char *fichier);

int decodeExecuteInstruction(uint32_t instruction, int64_t registres[], uint32_t *pc, uint8_t memoire[]);
int decodeExecuteR(uint32_t instruction, int64_t registres[]);
int decodeExecuteAddi(uint32_t instruction, int64_t registres[]);
int decodeExecuteLd(uint32_t instruction, int64_t registres[], uint8_t memoire[]);
int decodeExecuteSd(uint32_t instruction, int64_t registres[], uint8_t memoire[]);
int decodeExecuteB(uint32_t instruction, int64_t registres[], uint32_t *pc);
int decodeExecuteJal(uint32_t instruction, int64_t registres[], uint32_t *pc);

#endif