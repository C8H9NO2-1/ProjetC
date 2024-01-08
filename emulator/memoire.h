#ifndef __MEMOIRE_H__
#define __MEMOIRE_H__

uint32_t lire32bits(uint8_t memoire[], uint32_t adresse);
void ecrire32bits(uint8_t memoire[], uint32_t adresse, uint32_t x);

int64_t lire64bits(uint8_t memoire[], uint32_t adresse);
void ecrire64bits(uint8_t memoire[], uint32_t adresse, int64_t x);

#endif