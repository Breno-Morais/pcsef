#include <cpu.h>
#include <inttypes.h>
#include <ecran.h>
#include <horloge.h>
#include <procs.h>

proc **PROC_TABLE;
proc *actif;
sys_state state;

void kernel_start(void)
{
    // initialisations
    init_traitant_IT(32, traitant_IT_32);
    efface_ecran();

    // initialisation des structures de processus
    init_sys_state();
    PROC_TABLE = (proc **) malloc(SIZE_PROC_TABLE * sizeof(proc));

    proc proc_idle = { .pid = 0, .nom = "idle", .etat = ELU};
    proc_idle.regs = (uint32_t *) malloc(NUMBER_REGS * sizeof(uint32_t));
    proc_idle.exec_stack = (uint32_t *) malloc(SIZE_EXEC_STACK * sizeof(uint32_t));
    actif = &proc_idle;

    state.last_reserved_pid++;
    state.n_procs++;

    PROC_TABLE[0] = &proc_idle;
    cree_processus(proc1, "proc1");

    printf("[%s]", PROC_TABLE[0]->nom);
    printf("[%s]", PROC_TABLE[1]->nom);

    // démasquage des interruptions externes
    sti();

    // demarrage du processus par defaut
    idle();

    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

