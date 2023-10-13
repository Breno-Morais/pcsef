#include <cpu.h>
#include <inttypes.h>
#include <ecran.h>
#include <horloge.h>
#include <procs.h>

proc *PROC_TABLE[SIZE_PROC_TABLE] = {};

void kernel_start(void)
{
    // initialisations
    init_traitant_IT(32, traitant_IT_32);
    efface_ecran();

    // initialisation des structures de processus
    proc proc_idle = { .pid = 0, .nom = "idle", .etat = ELU, .regs = { 0 }, .exec_stack = { 0 }};

    proc proc_1 = { .pid = 1, .nom = "proc1", .etat = ACTIVABLE, .regs = { 0 }, .exec_stack = { 0 }};
    proc_1.exec_stack[0] = (uint32_t) proc1;
    proc_1.regs[1] = (uint32_t) proc_1.exec_stack;

    PROC_TABLE[0] = &proc_idle;
    PROC_TABLE[1] = &proc_1;

    // démasquage des interruptions externes
    sti();

    // demarrage du processus par defaut
    idle();

    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

