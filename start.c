#include <cpu.h>
#include <inttypes.h>
#include <ecran.h>
#include <horloge.h>

void kernel_start(void)
{
    // initialisations
    init_traitant_IT(32, traitant_IT_32);
    efface_ecran();

    // démasquage des interruptions externes
    sti();

    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

