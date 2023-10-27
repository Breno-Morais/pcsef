#include <procs.h>

void init_sys_state()
{
    state.last_reserved_pid = 0;
    state.n_procs = 0;
}

void ordonnance(void)
{
    proc *next = NULL;
    for(size_t i = 0; i < SIZE_PROC_TABLE; i++)
    {
        if(PROC_TABLE[i] != actif)
        {
            next = PROC_TABLE[i];
            break;
        }
    }
    
    proc *old = actif;
    old->etat = ACTIVABLE;
    next->etat = ELU;
    actif = next;

    ctx_sw(old->regs, actif->regs);
}

int32_t cree_processus(void (*code)(void), char *nom)
{
    uint64_t pid = state.last_reserved_pid + 1;


    proc *procPID = (proc *) malloc(sizeof(proc));
    procPID->pid = pid;
    procPID->nom = nom;
    procPID->etat = ACTIVABLE;
    procPID->regs = (uint32_t *) malloc(NUMBER_REGS * sizeof(uint32_t));
    procPID->exec_stack = (uint32_t *) malloc(SIZE_EXEC_STACK * sizeof(uint32_t));
    procPID->exec_stack[0] = (uint32_t) code;
    procPID->regs[1] = (uint32_t) procPID->exec_stack;

    PROC_TABLE[state.n_procs] = procPID;

    state.n_procs++;
    state.last_reserved_pid++;

    return (int32_t) pid;
}

char *mon_nom(void)
{
    return actif->nom;
}

int mon_pid(void)
{
    return (int) actif->pid;
}

void idle(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc1(void)
{
    for (;;) {
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}