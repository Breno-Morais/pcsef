#include <ecran.h>

uint16_t pos_lig = 0;
uint16_t pos_col = 0;

uint16_t *ptr_mem(uint32_t lig, uint32_t col)
{
	return (uint16_t *)(ECRAN_BASE + 2 * (lig * NCOL + col));
}

void ecrit_car(uint32_t lig, uint32_t col, char c)
{
	// A adiconar a possibilidade de adicionar cores
	uint16_t *ptr_ecran_car = ptr_mem(lig, col);

	*ptr_ecran_car = (COR_BLANC << 12) | (COR_NOIR << 8) | c;
}

void efface_ecran(void)
{
	int i, j;
	for (i = 0; i < NLIG; i++)
		for (j = 0; j < NCOL; j++)
			ecrit_car(i, j, CHAR_SPACE);
}

void place_curseur(uint32_t lig, uint32_t col)
{
	pos_lig = lig;
	pos_col = col;
	
	uint16_t pos_cursor = col + lig * NCOL;
	uint8_t bas_pos_cursor = (uint8_t)(pos_cursor & 0x00FF);
	uint8_t haut_pos_cursor = (uint8_t)((pos_cursor & 0xFF00) >> 8);

	outb(0x0F, 0x3D4);
	outb(bas_pos_cursor, 0x3D5);

	outb(0x0E, 0x3D4);
	outb(haut_pos_cursor, 0x3D5);
}

void traite_car(char c)
{
	switch (c)
	{
	case CHAR_BS:
		pos_col--;

		place_curseur(pos_lig, pos_col);
		break;

	case CHAR_HT:
		pos_col = (pos_col + 4) & ~0x03;

		place_curseur(pos_lig, pos_col);
		break;

	case CHAR_LF:
		pos_col = 0;
		pos_lig ++;

		place_curseur(pos_lig, pos_col);
		break;

	case CHAR_VT:
		pos_lig = (pos_lig + 2) & ~0x01;
		pos_col--;

		place_curseur(pos_lig, pos_col);
		break;

	case CHAR_FF:
		pos_col = 0;
		pos_lig = 0;
		efface_ecran();

		break;

	case CHAR_CR:
		pos_col = 0;

		place_curseur(pos_lig, pos_col);
		break;

	default:
		ecrit_car(pos_lig, pos_col, c);
		pos_col++;
		if (pos_col >= NCOL)
		{
			pos_col = 0;
			pos_lig++;
		}
		if (pos_lig >= NLIG)
		{
			pos_lig = 0;
		}

		place_curseur(pos_lig, pos_col);
		break;
	}
}

void supprime_ligne(void)
{
	for (int i = 0; i < NCOL; i++)
		ecrit_car(pos_lig, i, CHAR_SPACE);

	pos_lig--;
}

void defilement(void)
{
	uint16_t *org_lig = ptr_mem(pos_lig, 0);
	uint16_t *dst_lig = ptr_mem(pos_lig - 1, 0);

	memmove(dst_lig, org_lig, NCOL);
	supprime_ligne();
	place_curseur(pos_lig, pos_col);
}

void console_putbytes(const char *s, int len)
{
	for (int i = 0; i < len; i++)
	{
		traite_car(s[i]);
	}
}

void get_curseur(uint16_t *lig, uint16_t *col){
	*lig = pos_lig;
	*col = pos_col;
}

void printv(uint32_t*start, uint8_t size)
{
	printf("V: [");
	for(int i = 0; i < size - 1; i++)
	{
		printf("%X, ", start[i]);
	}
	printf("%X]\n", start[size-1]);
}