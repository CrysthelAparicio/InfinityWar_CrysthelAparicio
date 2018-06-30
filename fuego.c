#include "fuego.h"
#include "blit.h"
#include "naves.h"
#include "thanos.h"

extern int x_ofs;
extern int y_ofs;
extern nave todas_naves[NUM_NAVES];

fuego todos_fuegos[NUM_FUEGOS];

void nuevo_fuego(int x, int y)
{
	int n=0;
	while ( (todos_fuegos[n].x >= 0) && (++n<NUM_FUEGOS) ) ;

	if (n<=NUM_FUEGOS)
	{
		todos_fuegos[n].x = x;
		todos_fuegos[n].y = y;
	}
}

void inicia_fuegos()
{
	int i;
	for (i=0;i<NUM_FUEGOS;i++)
	{
		todos_fuegos[i].x = -1;
	}
}


void movimiento_fuegos()
{
	int i;
	for (i=0;i<NUM_FUEGOS;i++)
	{
		if (todos_fuegos[i].x >= 0)
		{
			int n;
			todos_fuegos[i].y--;
			if (todos_fuegos[i].y<0)
			{
				todos_fuegos[i].x = -1;
			}
			else
			{
				while ((n=colision_naves(todos_fuegos[i].x,todos_fuegos[i].y))>=0)
				{
					sangre_naves(n);
					todos_fuegos[i].x = -1;
				}
				if (colision_titan(todos_fuegos[i].x,todos_fuegos[i].y,COL_FUEGO)>=0)
				{
					todos_fuegos[i].x = -1;
				}
			}
		}
	}
}

void blit_fuegos()
{
	int i;
	for (i=0;i<NUM_FUEGOS;i++)
	{
		if (todos_fuegos[i].x >= 0)
		{
			blit_fuego(todos_fuegos[i].x+x_ofs,todos_fuegos[i].y+y_ofs);
		}
	}
}

void elimina_fuegos()
{
	int i;
	for (i=0;i<NUM_FUEGOS;i++)
	{
		if (todos_fuegos[i].x >= 0)
		{
			limpiar_fuego(todos_fuegos[i].x+x_ofs,todos_fuegos[i].y+y_ofs);
		}
	}
}