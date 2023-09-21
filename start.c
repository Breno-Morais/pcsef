#include <cpu.h>
#include <inttypes.h>
#include <ecran.h>

void kernel_start(void)
{
    efface_ecran();
    console_putbytes("1\b2\b345", 7);

    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

