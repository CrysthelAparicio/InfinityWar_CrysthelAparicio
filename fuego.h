#ifndef FUEGO_H
#define FUEGO_H

typedef struct
{
	int x;
	int y;
	void (*blit)(int,int);
	void (*clear)(int,int);
//	int estado; // pienso usarlo mas adelante
//	int tipo;  // x2
} fuego;

#define NUM_FUEGOS 25

void nuevo_fuego(int, int);
void inicia_fuegos(); 
void blit_fuegos();
void elimina_fuegos();
void movimiento_fuegos(); 

#endif 
