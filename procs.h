#ifndef __PROCS_H__
#define __PROCS_H__

#include <inttypes.h>
#include <segment.h>
#include <stdio.h>
#include <cpu.h>
#include <ecran.h>
#include <stdlib.h>
#include <tinyalloc.h>

#define PROC_NAME_SIZE_MAX 10
#define NUMBER_REGS 5
#define SIZE_EXEC_STACK 512
#define SIZE_PROC_TABLE 100

typedef enum _ETAT_PROC { ACTIVABLE, ELU } ETAT_PROC;

typedef struct _PROCESS_STRUCT{
    uint64_t pid;
    char *nom;
    ETAT_PROC etat;

    // Process Context. [%ebx, %esp, %ebp, %esi, %edi]
    uint32_t *regs;

    // Call function stack
    uint32_t *exec_stack;
} proc;

extern proc **PROC_TABLE;

extern proc *actif;

typedef struct _SYS_STATE_STRUCT{
    uint64_t last_reserved_pid;
    uint64_t n_procs;
} sys_state;

extern sys_state state;

void init_sys_state();

void ordonnance(void);

int32_t cree_processus(void (*code)(void), char *nom);

char *mon_nom(void);

int mon_pid(void);

void idle(void);

void proc1(void);

extern void ctx_sw(uint32_t* old_context, uint32_t* new_context);

#endif