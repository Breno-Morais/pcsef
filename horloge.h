#ifndef __HORLOGE_H__
#define __HORLOGE_H__

#include <inttypes.h>
#include <ecran.h>
#include <segment.h>

/* Write the string in the top-right corner */
void ecrit_temps(char* s, uint32_t size);

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void));

extern void traitant_IT_32(void);

void tic_PIT(void);

#endif