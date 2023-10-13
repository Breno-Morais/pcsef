#ifndef __PROCS_H__
#define __PROCS_H__

#include <inttypes.h>
#include <segment.h>
#include <stdio.h>
#include <cpu.h>
#include <ecran.h>

#define PROC_NAME_SIZE_MAX 10
#define NUMBER_REGS 5
#define SIZE_EXEC_STACK 512
#define SIZE_PROC_TABLE 2

typedef enum _ETAT_PROC { ACTIVABLE, ELU } ETAT_PROC;

typedef struct _PROCESS_STRUCT{
    uint64_t pid;
    char nom[PROC_NAME_SIZE_MAX];
    ETAT_PROC etat;

    // Process Context. [%ebx, %esp, %ebp, %esi, %edi]
    uint32_t regs[NUMBER_REGS];

    // Call function stack
    uint32_t exec_stack[SIZE_EXEC_STACK];
} proc;

extern proc *PROC_TABLE[SIZE_PROC_TABLE];

void idle(void);

void proc1(void);

extern void ctx_sw(uint32_t* old_context, uint32_t* new_context);

#endif