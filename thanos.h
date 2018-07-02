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
/*
En su memento cuando la memoria era escasa, era necesario exprimir al maximo lo poco de memoria que tenia una maquina. Si que si una sabia los limites que podian alcanzar una variable en un programa, podia crear variables que ocupen mas o menos memoria.
Uno de estos casos es el short. Al declarar un entero como short se le indica al compilador que utilice menos de los 32 bits usuales de memoria. De esta forma tenemos un programa mas compacto pero obviamente esa variable podia almacenar un rango de numero menor. El long encambio agranda el tamaño.
 */   
    unsigned char gemas;
// http://wiring.org.co/reference/es/unsignedchar.html para el unsigned
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