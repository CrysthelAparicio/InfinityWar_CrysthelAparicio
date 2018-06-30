#include "naves.h"
#include "blit.h"
#include "niveles.h"
#include "util.h"

extern int x_ofs;
extern int y_ofs;
extern int puntaje;
extern int juego_terminado;

const bitmask bitmask_grande_nave   = {0xF8,0xF8,0x70,0x00,0x00};
const bitmask bitmask_lit_nave   = {0xE0,0x40,0x00,0x00,0x00};
const bitmask bitmask_bola_nave  = {0xE0,0xE0,0x00,0x00,0x00};
const bitmask bitmask_limo_nave = {0xF8,0xF8,0x00,0x00,0x00};
const bitmask bitmask_dim_nave  = {0x80,0x00,0x00,0x00,0x00};

nave todas_naves[NUM_NAVES];


// Recta hacia abajo, velocidad media si el estado se inicializa a 0, velocidad máxima si -1 
void mover_nave_s(void *al_ptr)
{
	nave *al;
	al = (nave*)al_ptr;

	switch (al->estado)
	{
	case 0:
		al->estado=1;
		break;
	case 1:
		al->y++;
		al->estado=0;
		break;
	case -1:
		al->y++;
		break;
	}
	if ((al->y)>23) al->tipo=NV_NINGUNA;
}


/* Mueve hacia abajo en diagonal (izquierda si estado <0, derecha si> 0) hasta la mitad de la pantalla,
   luego baja y justo en la mitad de la pantalla.
   Finalmente, cuando el estado llega a 0, se mueve verticalmente. */
void mover_nave_osci(void *al_ptr)
{
	nave *al;
	al = (nave*)al_ptr;

	if (al->estado>0)
	{
		if ((al->y)<10) al->y++;
		al->x++;
		al->estado--;
		if ((al->x)>73) al->estado = -(al->estado);
	}
	else if (al->estado<0)
	{
		if ((al->y)<10) al->y++;
		al->x--;
		al->estado++;
		if ((al->x)<1) al->estado = -(al->estado);
	}
	else
	{
		al->y++;
		if ((al->y)>24) al->tipo=NV_NINGUNA;
	}
}

/* Se mueve hacia abajo como una serpiente, con x oscilando entre +3 y -3,
   a la mitad de velocidad; el estado debe inicializarse a 0 */
void mover_nave_serp(void *al_ptr)
{
	int xs=0;
	nave *al;
	al = (nave*)al_ptr;

	if (al->estado<0)
	{
		al->estado = -al->estado;
	}
	else
	{
		if (al->estado>10) xs = -1;
		else if (al->estado<8) xs = 1;
		if (al->estado == 0)
		{
			al->estado = 13;
			xs = -1;
		}

		al->x+=xs;
		al->y++;

		if (al->estado == 10) al->estado=1;
		if (al->estado == 8) al->estado=17;

		if (al->estado>9) al->estado--;
		else al->estado++;

		al->estado = -al->estado;

		if ((al->y)>24) al->tipo=NV_NINGUNA;
	}
}

/* Se mueve en diagonal (hacia la izquierda si el estado es <0, hacia la derecha si el estado> 0),
   a la mitad de velocidad si abs (estado) = 1, velocidad máxima si 2.
   Hay 2 tipos de buena inicialización:
   x <= 39, estado> 0
   x> = 39, estado <0 */
void mover_nave_diagonal(void *al_ptr)
{
	nave *al;
	al = (nave*)al_ptr;

	if (al->estado>0)
	{
		al->x++;
		switch (al->estado)
		{
		case 1:
			al->estado=3;
			break;
		case 3:
			al->estado=1;
		case 2:
			al->y++;
		}
	}
	else
	{
		al->x--;
		switch (al->estado)
		{
		case -1:
			al->estado = -3;
			break;
		case -3:
			al->estado = -1;
		case -2:
			al->y++;
		}
	}
	if ((al->y)>24) al->tipo=NV_NINGUNA;
}

void inicia_naves()
{
	int i;
	for (i=0;i<NUM_NAVES;i++)
		todas_naves[i].tipo=NV_NINGUNA;
}

// Dibuja todas las naves
void blit_naves()
{
	int i;
	for (i=0;i<NUM_NAVES;i++)
	{
		if (todas_naves[i].tipo != NV_NINGUNA)
		{
			todas_naves[i].blit(todas_naves[i].x+x_ofs,todas_naves[i].y+y_ofs);
		}
	}
}

// Elimina todas las naves
void elimina_naves()
{
	int i;
	for (i=0;i<NUM_NAVES;i++)
	{
		if (todas_naves[i].tipo != NV_NINGUNA)
		{
			todas_naves[i].clear(todas_naves[i].x+x_ofs,todas_naves[i].y+y_ofs);
		}
	}
}

// Hace que todas las naves se muevan
void mueve_naves()
{
	int i;
	if (!creacion_naves())
	{
		juego_terminado = 1;
	}
	for (i=0;i<NUM_NAVES;i++)
	{
		switch (todas_naves[i].tipo)
		{
		case AT_GRA:
		case AT_DIM:
		case AT_BOL:
		case AT_LI:
		case AT_PEQUE:
			todas_naves[i].move((void*)&todas_naves[i]);
			break;
		case NV_GR_EXP:
			switch (todas_naves[i].estado++)
			{
			case 0:
				todas_naves[i].blit = blit_explosion_3;
				todas_naves[i].clear = limpiar_explosion_3;
				break;
			case 2:
				todas_naves[i].blit = blit_explosion_4;
				todas_naves[i].clear = limpiar_explosion_4;
				break;
			case 4:
				todas_naves[i].blit = blit_explosion_3;
				todas_naves[i].clear = limpiar_explosion_3;
				break;
			case 6:
				todas_naves[i].blit = blit_explosion_2;
				todas_naves[i].clear = limpiar_explosion_2;
				break;
			case 8:
				todas_naves[i].blit = blit_explosion_1;
				todas_naves[i].clear = limpiar_explosion_1;
				todas_naves[i].tipo = AT_ULTIMO;
				break;
			}
			break;
		case NV_PE_EXP:
			switch (todas_naves[i].estado++)
			{
			case 0:
				todas_naves[i].blit = blit_explosion_2;
				todas_naves[i].clear = limpiar_explosion_2;
				break;
			case 2:
				todas_naves[i].blit = blit_explosion_3;
				todas_naves[i].clear = limpiar_explosion_3;
				break;
			case 4:
				todas_naves[i].blit = blit_explosion_2;
				todas_naves[i].clear = limpiar_explosion_2;
				break;
			case 6:
				todas_naves[i].blit = blit_explosion_1;
				todas_naves[i].clear = limpiar_explosion_1;
				todas_naves[i].tipo = AT_ULTIMO;
				break;
			}
			break;
		case AT_ULTIMO:
			todas_naves[i].tipo = NV_NINGUNA;
			break;
		}
	}
}

// Sangre num y puntaje de actualización 
void sangre_naves(int num)
{
	int i;
	for (i=0;i<MAX_ALT;i++)
		todas_naves[num].collide[i]=0x00;

	switch (todas_naves[num].tipo)
	{
	case AT_GRA:
		puntaje+=50;
		todas_naves[num].tipo=NV_GR_EXP;
		todas_naves[num].blit=blit_explosion_3;
		todas_naves[num].clear=limpiar_explosion_3;
		todas_naves[num].estado=0;
		todas_naves[num].x+=2;
		todas_naves[num].y++;
		break;
	case AT_PEQUE:
		puntaje+=50;
		todas_naves[num].tipo=NV_PE_EXP;
		todas_naves[num].blit=blit_explosion_2;
		todas_naves[num].clear=limpiar_explosion_2;
		todas_naves[num].estado=0;
		todas_naves[num].x++;
		break;
	case AT_LI:
		puntaje+=100;
		todas_naves[num].tipo=NV_GR_EXP;
		todas_naves[num].blit=blit_explosion_3;
		todas_naves[num].clear=limpiar_explosion_3;
		todas_naves[num].estado=0;
		todas_naves[num].x+=3;
		todas_naves[num].y++;
		break;
	case AT_DIM:
		puntaje+=300;
		todas_naves[num].tipo=NV_PE_EXP;
		todas_naves[num].blit=blit_explosion_2;
		todas_naves[num].clear=limpiar_explosion_2;
		todas_naves[num].estado=0;
		break;
	case AT_BOL:
		puntaje+=200;
		todas_naves[num].tipo=NV_PE_EXP;
		todas_naves[num].blit=blit_explosion_2;
		todas_naves[num].clear=limpiar_explosion_2;
		todas_naves[num].estado=0;
		todas_naves[num].x++;
		todas_naves[num].y++;
		break;
	}
}


// Verifica la colisión de todos las naves
// Devuelve -1 si no hay, de lo contrario, número de extranjero 
int colision_naves(int x, int y)
{
	int i;
	for (i=0;i<NUM_NAVES;i++)
	{
		if (todas_naves[i].tipo!=NV_NINGUNA)
		{
			int mask_x, mask_y;
			mask_x = x-todas_naves[i].x;
			mask_y = y-todas_naves[i].y;
			if ((mask_y>=0) && (mask_y<MAX_ALT) && (mask_x>=0) && (mask_x<8))
			{
				if ( (todas_naves[i].collide[mask_y] & (0x80 >> mask_x)) != 0 )
					return i;
			}
		}
	}
	return -1;
}