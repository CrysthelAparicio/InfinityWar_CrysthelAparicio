#ifndef ATTILAN_H
#define ATTILAN_H

#define MAX_DAMAGE 25

#define ATTI_ALTURA 2

typedef unsigned short s_bitmask[ATTI_ALTURA];

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
} nave_atti;

void inicia_atti(); 
void empieza_atti(); 

// Retorna 1 si atti muere
int atti_explota(); 

#define COL_NAVE 0
#define COL_FUEGO 1
#define COL_ESCUADRON 30
int colision_atti(int,int,int); 

void mover_atti();

void blit_atti();

void elimina_atti();

#endif