#ifndef _THANOS_H
#define _THANOS_H

#define MAX_DAMAGE 100

#define THANOS_ALTURA 5

typedef unsigned short s_bitmask[THANOS_ALTURA];

typedef struct
{
    int habilitado;
    int x;
    int y;
    void (*blit)(int,int,int);
    void (*clear)(int,int);
    short int damage;
    unsigned char gemas;
    s_bitmask collide;
} nave_titan;

void inicia_titan(); 
void empieza_thanos(); 

// Retorna 1 si thanos esta muerto
int thanos_explota(); 

#define COL_NAVE 0
#define COL_FUEGO 1
#define COL_ESCUDO 2
int colision_titan(int,int,int); //titan

void mover_titan();

void blit_titan();

void elimina_titan();

#endif