#ifndef ESCUDO_H
#define ESCUDO_H

typedef struct
{
	int x;
	int y;
	void (*blit)(int,int,int);
	void (*clear)(int,int);
	int estado;
} escudo;

#define ESCUDO_MAX 100  // Duracion del tiempo 
#define ESCUDO_MIN -100 // Recarga el tiempo
#define ESCUDO_PASO 40  // Deberia ser mas del ESCUDO_MAX 

void inicia_escudos(); 
void abrir_escudos(int, int);
void blit_escudos();
void limpia_escudos(); 
/* En realidad, no se mueve, pero he llamado a esta función "mover"
   para la coherencia con otras funciones de movimiento. Solo verifica
   colisiones y carga de escudo */
void mover_escudos(); 

#endif 