#ifndef __ECRAN_H__
#define __ECRAN_H__

#include <inttypes.h>
#include <stdio.h>
#include <cpu.h>
#include <string.h>
#define ECRAN_BASE 0xb8000
#define NLIG 25
#define NCOL 80

#define CHAR_SPACE 32
#define CHAR_NUL 0x00
#define CHAR_BEL 0x07
#define CHAR_BS 0x08
#define CHAR_HT 0x09
#define CHAR_LF 0x0B
#define CHAR_VT 0x08
#define CHAR_FF 0x0C
#define CHAR_CR 0x0D
#define CHAR_SUB 0x1A
#define CHAR_ESC 0x1B

#define COR_NOIR 0
#define COR_BLEU 1
#define COR_VERT 2
#define COR_CYAN 3
#define COR_ROUGE 4
#define COR_MAGENTA 5
#define COR_MARRON 6
#define COR_GRIS 7
#define COR_GRIS_FONCE 8
#define COR_BLEU_CLAIR 9
#define COR_VERT_CLAIR 10
#define COR_CYAN_CLAIR 11
#define COR_ROUGE_CLAIR 12
#define COR_MAGENTA_CLAIR 13
#define COR_JAUNE 14
#define COR_BLANC 15


uint16_t *ptr_mem(uint32_t lig, uint32_t col);

void ecrit_car(uint32_t lig, uint32_t col, char c);

void efface_ecran(void);

void place_curseur(uint32_t lig, uint32_t col);

void traite_car(char c);

void defilement(void);

void console_putbytes(const char *s, int len);

#endif
