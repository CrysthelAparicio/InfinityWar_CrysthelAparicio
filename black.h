#ifndef BLACK_H
#define BLACK_H

#define MAX_DAMAGE 50

#define BLACK_ALTURA 3

typedef unsigned short s_bitmask[BLACK_ALTURA];

typedef struct
{
    int habilitado;
    int x;
    int y;
    void (*blit)(int,int,int);
    void (*clear)(int,int);
    short int damage;
    unsigned char rafagas;
    s_bitmask collide;
} nave_black;

void inicia_black(); 
void empieza_black(); 

// Retorna 1 si black muere
int black_explota(); 

#define COL_NAVE 0
#define COL_FUEGO 1
#define COL_RAFAGA 3
int colision_black(int,int,int); 

void mover_black();

void blit_black();

void elimina_black();

#endif