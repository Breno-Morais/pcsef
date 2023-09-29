#include <horloge.h>

void ecrit_temps(char* s, uint32_t size)
{
    uint16_t prev_lig, prev_col, col, lig;

    get_curseur(&prev_lig, &prev_col);

    lig = 0;
    col = NCOL - size;

    place_curseur(lig, col);
    console_putbytes(s, size);
    place_curseur(prev_lig, prev_col);
}

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void))
{
    uint32_t premier_mot = (KERNEL_CS << 16) | ((uint32_t)traitant);
    uint32_t deux_mot =(((uint32_t)traitant) << 16) | 0x8E00;

    uint32_t *IDT = (uint32_t*) 0x1000;
    IDT[num_IT * 2] = premier_mot;
    IDT[num_IT * 2 + 1] = deux_mot;   
}

void tic_PIT(void){
    traite_car('H');
}
