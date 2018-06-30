#ifndef NAVES_H
#define NAVESS_H

#define NV_NINGUNA   -1
#define AT_ULTIMO -2
#define NV_GR_EXP  8
#define NV_PE_EXP  7
#define AT_THANOS_1 6
#define AT_THANOS_2 5
#define AT_DIM     4
#define AT_LI    3
#define AT_BOL     2
#define AT_GRA      1
#define AT_PEQUE   0

#define MAX_ALT 5

typedef char bitmask[MAX_ALT];

typedef struct
{
	int x;
	int y;
	int tipo; // Aqui es para ver las definiciones
	void (*blit)(int,int);
	void (*clear)(int,int);
	void (*move)(void *);
	short int estado;
	bitmask collide;
} nave;

#define NUM_NAVES 10

// Movimiento de las naves
void mover_nave_s(void *);
void mover_nave_osci(void *);
void mover_nave_serp(void *);
void mover_nave_diagonal(void *);

void inicia_naves();

// Dibujo las naves
void blit_naves();

// Elimino las naves
void elimina_naves();

// Hago los movimientos de las naves
void mueve_naves();

// Sangre de las naves, num y updateo el puntaje
void sangre_naves(int);

// Chequea las colisiones de las naves
int colision_naves(int, int);

#endif 