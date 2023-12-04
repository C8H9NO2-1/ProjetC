#ifndef __FONCTIONS_H__
#define __FONCTIONS_H__

#include <stdbool.h>

void remplace(char *chaine);
char* recupereNomInstruction(char *instruction);
int charVersEntier(char *chaine);
int registreVersEntier(char *registre, char **listeRegistre);

uint32_t formatR(char *instruction, char** listeRegistre);

#endif