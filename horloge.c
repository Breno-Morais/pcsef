#include <horloge.h>

int TICKS = 0;

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
    // 0 - acknowledgment of the interrupt
    outb(0x20,0x20);
    TICKS+=1;
    // 1 - create time String
    char temps[9];
    sprintf(temps, "%02u:%02u:%02u", (TICKS/(CLOCK_FREQ6060))%24, (TICKS/(CLOCK_FREQ60))%60, (TICKS/CLOCK_FREQ)%60);
    // 2 - Display
    ecrit_temps(temps, strlen(temps));
}

void regler_frequence(void){
    // 1) Send command 0x34 to port 0x43
    outb((uint8_t) 0x34, (uint16_t) 0x43);
    // 2) Send 8 least significant bits
    outb((QUARTZ / CLOCK_FREQ) & 0xFF, (uint16_t) 0x40);
    // 3) Send 8 most significant bits
    outb(((QUARTZ / CLOCK_FREQ) >> 8) & 255, (uint16_t) 0x40);
}

void masque_IRQ(uint32_t num_IRQ, uint8_t masque){
    // Read the current mask value
    uint8_t current_mask = inb(0x21);
    // Set bit N to zero:
    current_mask = current_mask & (~(1<<num_IRQ));
    // Set bit N to masque value
    current_mask = current_mask | (masque<<num_IRQ);
    // Send updated mask to port 0x21
    outb(current_mask, (uint16_t) 0x21);
}
