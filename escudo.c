#include "escudo.h"
#include "blit.h"
#include "naves.h"
#include "thanos.h"
#include "defs.h"

escudo scudo;

extern int x_ofs;
extern int y_ofs;
extern nave todas_naves[NUM_NAVES];

void inicia_escudos()
{
	scudo.x = -5;
	scudo.estado = ESCUDO_MIN; // Baja y recarga
	scudo.blit = blit_escudo;
	scudo.clear = limpiar_escudo;
}

void abrir_escudos(int x, int y)
{
	if ( (scudo.estado>0) && (scudo.x<-1) )
	{
		scudo.x = x;
		scudo.y = y;
	}
}

void mover_escudos()
{
	if (scudo.x<-1)
	{
		if (scudo.estado<ESCUDO_MAX)
			scudo.estado++;
	}
	else // El escudo esta encendido
	{
		scudo.estado--;
		if (scudo.estado>0)
		{
			int i,rel_x,rel_y;
			// Chequea las colisiones
			for (i=0;i<NUM_NAVES;i++)
			{
				rel_x=scudo.x-todas_naves[i].x;
				rel_y=scudo.y-todas_naves[i].y;
				if ( (rel_y>=0) && (rel_y<MAX_ALT) &&
				     (rel_x > -9) && (rel_x < 8) )
				{
					int shift;
					if (rel_x >= -1) shift=0x1FF>>(rel_x+1);
					else shift=0x1FF<<(-(rel_x+1));
					if ((todas_naves[i].collide[rel_y] & shift) != 0 )
					{
						sangre_naves(i);
					}
				}
			}
			for (i=0;i<9;i++)
				colision_titan(scudo.x+i,scudo.y,COL_ESCUDO);
		}
		else
		{
			scudo.estado = ESCUDO_MIN;
			scudo.x = -5;
		}
	}
}

void blit_escudos()
{
	if (scudo.x >= -1)
	{
		scudo.blit(scudo.x+x_ofs,scudo.y+y_ofs,(scudo.estado/ESCUDO_PASO)+1);
	}
	else if (scudo.estado>0) blit_escudo_carga(x_ofs,y_ofs,scudo.estado/(ESCUDO_MAX/20));
}

void limpia_escudos()
{
	if (scudo.x >= -1)
	{
		scudo.clear(scudo.x+x_ofs,scudo.y+y_ofs);
	}
	limpiar_escudo_carga(x_ofs,y_ofs);
}


