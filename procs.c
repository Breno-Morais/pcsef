#include <procs.h>

void idle(void)
{
    for (int i = 0; i < 3; i++)
    {
        printf("[idle] je tente de passer la main a proc1...\n");

        printv(PROC_TABLE[0]->regs, NUMBER_REGS);
        printv(PROC_TABLE[1]->regs, NUMBER_REGS);

        ctx_sw(PROC_TABLE[0]->regs, PROC_TABLE[1]->regs);
        printf("[idle] proc1 m'a redonne la main\n");
    }
    printf("[idle] je bloque le systeme\n");
    hlt();
}
void proc1(void)
{
        printf("[proc1] idle m'a donne la main\n");
        printf("[proc1] je tente de lui la redonner...\n");

        printv(PROC_TABLE[0]->regs, NUMBER_REGS);
        printv(PROC_TABLE[1]->regs, NUMBER_REGS);
        
        ctx_sw(PROC_TABLE[1]->regs, PROC_TABLE[0]->regs);
}