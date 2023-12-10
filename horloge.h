#ifndef __HORLOGE_H__
#define __HORLOGE_H__

#include <inttypes.h>
#include <ecran.h>
#include <segment.h>

#define QUARTZ 0x1234DD
#define CLOCK_FREQ6060 CLOCK_FREQ60 * 60
#define CLOCK_FREQ60 CLOCK_FREQ * 60
#define CLOCK_FREQ 50

void ecrit_temps(char* s, uint32_t size);

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void));

extern void traitant_IT_32(void);

void tic_PIT(void);

void regler_frequence(void);

void masque_IRQ(uint32_t num_IRQ, uint8_t masque);

#endif