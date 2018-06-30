#include "niveles.h"
#include "naves.h"
#include "thanos.h"
#include "blit.h"
#include "util.h"
#include "defs.h"

#ifdef DEBUG_LEV
#include <ncurses.h>
extern WINDOW *term;
#endif

// Puntaje necesitado para matar a Thanos
#ifdef NIVEL_DIFICIL
#define PUNTAJE_NECESITADO 4000
#else
#ifdef NIVEL_FACIL
#define PUNTAJE_NECESITADO  2000
#endif
#endif

#ifndef PUNTAJE_NECESITADO
#define PUNTAJE_NECESITADO  3000
#endif

extern int puntaje;

extern nave todas_naves[NUM_NAVES];

extern const bitmask bitmask_grande_nave;
extern const bitmask bitmask_lit_nave;
extern const bitmask bitmask_bola_nave;
extern const bitmask bitmask_limo_nave;
extern const bitmask bitmask_dim_nave;

#define FRAME_SIZE     9

#define MOVER_DERECHO  1
#define MOVER_OSCILANTE 2
#define MOVER_DIAGONAL  3
#define MOVER_SERPIENTE   4

char level_1[] = {
	
0x00,0x00, 0, AT_PEQUE, 39,-5, 0, MOVER_DERECHO, -1,
0x00,0x04, 1, AT_PEQUE, 39,-5, 0, MOVER_DERECHO, -1,
0x00,0x08, 2, AT_PEQUE, 39,-5, 0, MOVER_DERECHO, -1,
0x00,0x0C, 3, AT_PEQUE, 39,-5, 0, MOVER_DERECHO, -1,
0x00,0x10, 4, AT_PEQUE, 39,-5, 0, MOVER_DERECHO, -1,

0x00,0x30, 5, AT_PEQUE, 39,-5, -1, MOVER_DERECHO, -1,
0x00,0x32, 6, AT_PEQUE, 41,-5, -1, MOVER_DERECHO, -1,
0x00,0x34, 7, AT_PEQUE, 38,-5, -1, MOVER_DERECHO, -1,
0x00,0x36, 8, AT_PEQUE, 40,-5, -1, MOVER_DERECHO, -1,
0x00,0x38, 9, AT_PEQUE, 38,-5, -1, MOVER_DERECHO, -1,

0x01,0x60, 0, NV_NINGUNA,    0, 0,  0, MOVER_DERECHO,  -1,
};


char level_2[] = {
0x00,0x00, 0, AT_BOL,   48,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x02, 1, AT_DIM,   49,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x04, 2, AT_DIM,   49,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x06, 3, AT_DIM,   49,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x08, 4, AT_DIM,   49,-3,  0, MOVER_SERPIENTE, -1,

0x00,0x10, 5, AT_BOL,   27,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x12, 6, AT_DIM,   28,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x14, 7, AT_DIM,   28,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x16, 8, AT_DIM,   28,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x18, 9, AT_DIM,   28,-3,  0, MOVER_SERPIENTE, -1,

0x00,0x36, 0, AT_BOL,   72,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x38, 1, AT_DIM,   73,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x3A, 2, AT_DIM,   73,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x3C, 3, AT_DIM,   73,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x3E, 4, AT_DIM,   73,-3,  0, MOVER_SERPIENTE, -1,

0x00,0x46, 5, AT_BOL,    6,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x48, 6, AT_DIM,    7,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x4A, 7, AT_DIM,    7,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x4C, 8, AT_DIM,    7,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x4E, 9, AT_DIM,    7,-3,  0, MOVER_SERPIENTE, -1,

0x00,0x70, 0, AT_BOL,   59,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x72, 1, AT_DIM,   60,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x74, 2, AT_DIM,   60,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x76, 3, AT_DIM,   60,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x78, 4, AT_DIM,   60,-3,  0, MOVER_SERPIENTE, -1,

0x00,0x80, 5, AT_BOL,   12,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x82, 6, AT_DIM,   13,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x84, 7, AT_DIM,   13,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x86, 8, AT_DIM,   13,-3,  0, MOVER_SERPIENTE, -1,
0x00,0x88, 9, AT_DIM,   13,-3,  0, MOVER_SERPIENTE, -1,

0x00,0xA6, 0, AT_BOL,   39,-3,  0, MOVER_SERPIENTE, -1,
0x00,0xA8, 1, AT_DIM,   40,-3,  0, MOVER_SERPIENTE, -1,
0x00,0xAA, 2, AT_DIM,   40,-3,  0, MOVER_SERPIENTE, -1,
0x00,0xAC, 3, AT_DIM,   40,-3,  0, MOVER_SERPIENTE, -1,
0x00,0xAE, 4, AT_DIM,   40,-3,  0, MOVER_SERPIENTE, -1,

0x00,0xB6, 5, AT_BOL,   44,-3,  0, MOVER_SERPIENTE, -1,
0x00,0xB8, 6, AT_DIM,   45,-3,  0, MOVER_SERPIENTE, -1,
0x00,0xBA, 7, AT_DIM,   45,-3,  0, MOVER_SERPIENTE, -1,
0x00,0xBC, 8, AT_DIM,   45,-3,  0, MOVER_SERPIENTE, -1,
0x00,0xBE, 9, AT_DIM,   45,-3,  0, MOVER_SERPIENTE, -1,

0x00,0xF5, 0, NV_NINGUNA, 0,0,0, MOVER_DERECHO, -1,
};

char level_3[] = {
0x00,0x00, 0, AT_LI,  3,-3,  70, MOVER_OSCILANTE, -1,
0x00,0x0D, 1, AT_DIM,  19,11,  -1, MOVER_DERECHO,  0,
0x00,0x15, 2, AT_DIM,  27,11,  -1, MOVER_DERECHO,  0,
0x00,0x1D, 3, AT_DIM,  35,11,  -1, MOVER_DERECHO,  0,
0x00,0x25, 4, AT_DIM,  43,11,  -1, MOVER_DERECHO,  0,
0x00,0x2D, 5, AT_DIM,  51,11,  -1, MOVER_DERECHO,  0,
0x00,0x35, 6, AT_DIM,  59,11,  -1, MOVER_DERECHO,  0,
0x00,0x3D, 7, AT_DIM,  67,11,  -1, MOVER_DERECHO,  0,

0x00,0x49, 1, AT_LI, 72,-3, -70, MOVER_OSCILANTE, -1,
0x00,0x56, 2, AT_DIM,  60,11,  -1, MOVER_DERECHO,  1,
0x00,0x5E, 3, AT_DIM,  52,11,  -1, MOVER_DERECHO,  1,
0x00,0x66, 4, AT_DIM,  44,11,  -1, MOVER_DERECHO,  1,
0x00,0x6E, 5, AT_DIM,  36,11,  -1, MOVER_DERECHO,  1,
0x00,0x76, 6, AT_DIM,  28,11,  -1, MOVER_DERECHO,  1,
0x00,0x7E, 7, AT_DIM,  20,11,  -1, MOVER_DERECHO,  1,
0x00,0x86, 8, AT_DIM,  12,11,  -1, MOVER_DERECHO,  1,

0x00,0xB0, 0, AT_LI,  3,-3,  70, MOVER_OSCILANTE, -1,
0x00,0xBD, 1, AT_DIM,  19,11,  -1, MOVER_DERECHO,  0,
0x00,0xC5, 2, AT_DIM,  27,11,  -1, MOVER_DERECHO,  0,
0x00,0xCD, 3, AT_DIM,  35,11,  -1, MOVER_DERECHO,  0,
0x00,0xD5, 4, AT_DIM,  43,11,  -1, MOVER_DERECHO,  0,
0x00,0xDD, 5, AT_DIM,  51,11,  -1, MOVER_DERECHO,  0,
0x00,0xE5, 6, AT_DIM,  59,11,  -1, MOVER_DERECHO,  0,
0x00,0xED, 7, AT_DIM,  67,11,  -1, MOVER_DERECHO,  0,

0x00,0xF9, 1, AT_LI, 72,-3, -70, MOVER_OSCILANTE, -1,
0x01,0x06, 2, AT_DIM,  60,11,  -1, MOVER_DERECHO,  1,
0x01,0x0E, 3, AT_DIM,  52,11,  -1, MOVER_DERECHO,  1,
0x01,0x16, 4, AT_DIM,  44,11,  -1, MOVER_DERECHO,  1,
0x01,0x1E, 5, AT_DIM,  36,11,  -1, MOVER_DERECHO,  1,
0x01,0x26, 6, AT_DIM,  28,11,  -1, MOVER_DERECHO,  1,
0x01,0x2E, 7, AT_DIM,  20,11,  -1, MOVER_DERECHO,  1,
0x01,0x36, 8, AT_DIM,  12,11,  -1, MOVER_DERECHO,  1,

0x01,0x50, 0, NV_NINGUNA, 0,0,0, MOVER_DERECHO, -1,
};

char level_4[] = {
0x00,0x00, 2, AT_GRA,   12,-5,  -1, MOVER_DERECHO, -1,
0x00,0x03, 3, AT_GRA,   45,-5,  -1, MOVER_DERECHO, -1,
0x00,0x06, 4, AT_GRA,   75,-5,  -1, MOVER_DERECHO, -1,
0x00,0x09, 5, AT_GRA,    5,-5,  -1, MOVER_DERECHO, -1,
0x00,0x0C, 6, AT_GRA,   34,-5,  -1, MOVER_DERECHO, -1,
0x00,0x0F, 7, AT_GRA,   57,-5,  -1, MOVER_DERECHO, -1,
0x00,0x12, 8, AT_GRA,   46,-5,  -1, MOVER_DERECHO, -1,
0x00,0x15, 9, AT_GRA,   61,-5,  -1, MOVER_DERECHO, -1,
0x00,0x18, 0, AT_GRA,   74,-5,  -1, MOVER_DERECHO, -1,
0x00,0x1B, 1, AT_GRA,   15,-5,  -1, MOVER_DERECHO, -1,
0x00,0x1E, 2, AT_GRA,   34,-5,  -1, MOVER_DERECHO, -1,
0x00,0x21, 3, AT_GRA,   21,-5,  -1, MOVER_DERECHO, -1,
0x00,0x24, 4, AT_GRA,   51,-5,  -1, MOVER_DERECHO, -1,
0x00,0x27, 5, AT_GRA,   14,-5,  -1, MOVER_DERECHO, -1,
0x00,0x2A, 6, AT_GRA,   62,-5,  -1, MOVER_DERECHO, -1,
0x00,0x2D, 7, AT_GRA,    3,-5,  -1, MOVER_DERECHO, -1,

0x00,0x30, 8, AT_GRA,   40,-5,  -1, MOVER_DERECHO, -1,
0x00,0x33, 9, AT_GRA,   59,-5,  -1, MOVER_DERECHO, -1,
0x00,0x36, 0, AT_GRA,   13,-5,  -1, MOVER_DERECHO, -1,
0x00,0x39, 1, AT_GRA,   35,-5,  -1, MOVER_DERECHO, -1,
0x00,0x3C, 2, AT_GRA,   72,-5,  -1, MOVER_DERECHO, -1,
0x00,0x3F, 3, AT_GRA,    2,-5,  -1, MOVER_DERECHO, -1,
0x00,0x42, 4, AT_GRA,   10,-5,  -1, MOVER_DERECHO, -1,
0x00,0x45, 5, AT_GRA,   51,-5,  -1, MOVER_DERECHO, -1,
0x00,0x48, 6, AT_GRA,   39,-5,  -1, MOVER_DERECHO, -1,
0x00,0x4B, 7, AT_GRA,   63,-5,  -1, MOVER_DERECHO, -1,
0x00,0x4E, 8, AT_GRA,   24,-5,  -1, MOVER_DERECHO, -1,
0x00,0x51, 9, AT_GRA,   70,-5,  -1, MOVER_DERECHO, -1,
0x00,0x54, 0, AT_GRA,   42,-5,  -1, MOVER_DERECHO, -1,
0x00,0x57, 1, AT_GRA,    9,-5,  -1, MOVER_DERECHO, -1,
0x00,0x5A, 2, AT_GRA,   68,-5,  -1, MOVER_DERECHO, -1,
0x00,0x5D, 3, AT_GRA,   40,-5,  -1, MOVER_DERECHO, -1,

0x00,0x7B, 0, NV_NINGUNA, 0,0,0, MOVER_DERECHO, -1,
};

char *level;

void inicia_niveles()
{
#ifndef RANDOM_LEVELS
// Algoritmo Secuencial
	level=level_1;
#else
// Algoritmo Random 
	switch (rrand(1,4))
	{
	case 1:
		level=level_1;
		break;
	case 2:
		level=level_2;
		break;
	case 3:
		level=level_3;
		break;
	case 4:
		level=level_4;
		break;
	}
#endif
}

char *next_level(const char *actual)
{
	char *next=level_1;
#ifndef RANDOM_LEVELS
	if (actual==level_1) next = level_2;
	else if (actual==level_2) next = level_3;
	else if (actual==level_3) next = level_4;
	else if ((actual==level_4) && (puntaje >= PUNTAJE_NECESITADO)) next = NULL;
	else next = level_1;

#else
	switch (rrand(1,4))
	{
	case 1:
		next=level_1;
		break;
	case 2:
		next=level_2;
		break;
	case 3:
		next=level_3;
		break;
	case 4:
		next=level_4;
		break;
	}
	if (puntaje>=PUNTAJE_NECESITADO)
	{
		next = NULL;
	}
#endif
	return next;
}

int thanos_nivel(unsigned short int moment) 
{
	static int start_end=0;
	if (!(thanos_explota()))
	{
		if (moment == 20)
		{
			empieza_thanos();
		}
		else if (moment > 30)
		{
			int i;
			for (i=4;i<NUM_NAVES;i++)
			{
				if (todas_naves[i].tipo == NV_NINGUNA)
				{
					if (rrand(1,100)>90)
					{
						int n;
						todas_naves[i].tipo = AT_PEQUE;
						todas_naves[i].x = rrand(0,77);
						todas_naves[i].y = -3;
						todas_naves[i].estado = 0;
						todas_naves[i].blit = blit_peque_nave;
						todas_naves[i].clear = limpiar_peque_nave;
						todas_naves[i].move = mover_nave_s;
						for (n=0;n<MAX_ALT;n++)
							todas_naves[i].collide[n] = bitmask_lit_nave[n];
					}
				}
			}
		}
		return 0;
	}
	else
	{
		if (start_end++<50)
			return 0;
		else
			return 1;
	}
}

int creacion_naves()
{
	static unsigned short int moment=0;
	static int lev_count=0;
	static int ended=0;

	if (ended)
	{
#ifdef DEBUG_LEV
		mvwprintw(term,24,0,"%X over   ",moment++);
		return 1;
#else
	// Lazo, es genial como el delay y el loop funcionan igual que la guitarra
		ended = 0;
		lev_count = 0;
		moment = 0;
		if (level==NULL)
		{
			return 0;
		}
		else
		{
			level = next_level(level);
		}
#endif
	}

	if (level==NULL)
	{
		ended=thanos_nivel(moment);
	}
	else
	{
		while ( moment == ( ((unsigned char)level[lev_count]<<8) | (unsigned char)level[lev_count+1] ) )
		{
			if ( (level[lev_count+8] < 0) ||
			      ((todas_naves[(int)level[lev_count+8]].tipo != NV_NINGUNA) &&
			       (todas_naves[(int)level[lev_count+8]].tipo != NV_GR_EXP) &&
			       (todas_naves[(int)level[lev_count+8]].tipo != NV_PE_EXP) &&
			       (todas_naves[(int)level[lev_count+8]].tipo != AT_ULTIMO)) )
			{
				int ar_num;
				int n;

				ar_num = level[lev_count+2];

				todas_naves[ar_num].tipo = level[lev_count+3];

				switch (todas_naves[ar_num].tipo)
				{
					
				case AT_PEQUE:
					todas_naves[ar_num].blit=blit_peque_nave;
					todas_naves[ar_num].clear=limpiar_peque_nave;
					for (n=0;n<MAX_ALT;n++)
						todas_naves[ar_num].collide[n]=bitmask_lit_nave[n];
					break;
					
				case AT_GRA:
					todas_naves[ar_num].blit=blit_grande_nave;
					todas_naves[ar_num].clear=limpiar_grande_nave;
					for (n=0;n<MAX_ALT;n++)
						todas_naves[ar_num].collide[n]=bitmask_grande_nave[n];
					break;
				case AT_LI:
					todas_naves[ar_num].blit=blit_limo_nave;
					todas_naves[ar_num].clear=limpiar_limo_nave;
					for (n=0;n<MAX_ALT;n++)
						todas_naves[ar_num].collide[n]=bitmask_limo_nave[n];
					break;
				case AT_BOL:
					todas_naves[ar_num].blit=blit_bola_nave;
					todas_naves[ar_num].clear=limpiar_bola_nave;
					for (n=0;n<MAX_ALT;n++)
						todas_naves[ar_num].collide[n]=bitmask_bola_nave[n];
					break;
				case AT_DIM:
					//todas_naves[ar_num].blit=blit_mini_nave;
					//todas_naves[ar_num].clear=limpiar_mini_nave;
					for (n=0;n<MAX_ALT;n++)
						todas_naves[ar_num].collide[n]=bitmask_dim_nave[n];
					break;
				case NV_NINGUNA:
					ended = 1;
					break;
				}

				todas_naves[ar_num].x = (signed char)level[lev_count+4];
				todas_naves[ar_num].y = (signed char)level[lev_count+5];
				todas_naves[ar_num].estado = level[lev_count+6];
				switch (level[lev_count+7])
				{
				case MOVER_DERECHO:
					todas_naves[ar_num].move = mover_nave_s;
					break;
				case MOVER_OSCILANTE:
					todas_naves[ar_num].move = mover_nave_osci;
					break;
				case MOVER_DIAGONAL:
					todas_naves[ar_num].move = mover_nave_diagonal;
					break;
				case MOVER_SERPIENTE:
					todas_naves[ar_num].move = mover_nave_serp;
					break;
				}
				todas_naves[ar_num].tipo = level[lev_count+3];
			}

			lev_count += FRAME_SIZE;
		}
	}
	moment++;

#ifdef DEBUG_LEV
	mvwprintw(term,24,0,"%X   ",moment);
#endif

	return 1;
}