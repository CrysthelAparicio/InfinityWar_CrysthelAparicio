#include "thanos.h"
#include "naves.h"
#include "blit.h"
#include "util.h"
#include "defs.h"

extern int x_ofs;
extern int y_ofs;
extern int puntaje;
extern nave todas_naves[NUM_NAVES];
extern const bitmask bitmask_dim_nave;

const s_bitmask s_bitmask_thanos = {0x7FC0,0xFFE0,0x7FC0,0x3F80,0x7FC0};

nave_titan thanos;

void empieza_thanos()
{
    thanos.habilitado = 1;
}

int thanos_explota()
{
    return (thanos.damage <= 0);
}

void inicia_titan()
{
    int i;
    thanos.habilitado = 0;
    thanos.x = rrand(10,60);
    thanos.y = -(THANOS_ALTURA + 1);
    thanos.blit = blit_thanos;
    thanos.clear = limpiar_thanos;
    thanos.damage = MAX_DAMAGE;
    thanos.gemas = 0x0F;
    for (i=0;i<THANOS_ALTURA;i++)
    thanos.collide[i]=s_bitmask_thanos[i];
}

int colision_titan(int x, int y, int tipo)
{
    if (thanos.habilitado)
    {
        int rel_x, rel_y;
        int ret=-1;

        rel_x = x - thanos.x;
        rel_y = y - thanos.y;
        if ( (rel_x >= 0) && (rel_x < 16) &&
         (rel_y >= 0) && (rel_y < THANOS_ALTURA) )
        {
            if ( (thanos.collide[rel_y] & (0x8000 >> rel_x)) != 0 )
            {
                int living;
                living = (thanos.damage>0);
                ret = 1;
                switch (tipo)
                {
                case COL_FUEGO:
                    thanos.damage -= 5;
                    break;
                case COL_ESCUDO:
                    thanos.damage -= 1;
                    break;
                case COL_NAVE:
                    break;
                }

                //Controla si thanos muere
                if ((living) && (thanos.damage<=0))
                {
                    puntaje+=5000;
                }
            }
        }

        return ret;
    }
    else return -1;
}

// retorna el numero de la nave
int fuego_gema(unsigned char *gemas)
{
    int ret;
    if (*gemas & 0x02)
    {
        ret = 1;
        if (todas_naves[ret].tipo != NV_NINGUNA)
        {
            return -1;
        }
        *gemas &= 0x0D;
    }
    else if (*gemas & 0x04)
    {
        ret = 2;
        if (todas_naves[ret].tipo != NV_NINGUNA)
        {
            return -1;
    }
        *gemas &= 0x0B;
    }
    else if (*gemas & 0x01)
    {
        ret = 0;
        if (todas_naves[ret].tipo != NV_NINGUNA)
    {
    return -1;
    }
        *gemas &= 0x0E;
    }
    else if (*gemas & 0x08)
    {
        ret = 4;
        if (todas_naves[ret].tipo != NV_NINGUNA)
        {
            return -1;
        }
            *gemas &= 0x07;
    }
        else return -1;

        return ret;
}

void tirar_gemas(unsigned char *gemas)
{
    if ((*gemas & 0x08)==0)
    {
    *gemas |= 0x08;
    }
    else if ((*gemas & 0x01)==0)
    {
        *gemas |= 0x01;
    }
    else if ((*gemas & 0x04)==0)
    {
        *gemas |= 0x04;
    }
    else if ((*gemas & 0x02)==0)
    {
        *gemas |= 0x02;
    }
}

/* Esta función mueve a Thanos.
El flota a izquierda y derecha en la parte superior de la pantalla, al azar arrasando hacia abajo.
*/
void mover_thanos(void *q_ptr)
{
    static int xs=1;
    static int ys=0;
    nave_titan *al;
    al = (nave_titan *)q_ptr;

    if (al->habilitado)
    {
        if (al->damage > 0)
        {
            if (al->y < 2)
            {
                ys = 1;
            }
            else if (al->y == 2)
            {
                if (rrand(1,100)>95)
            {
                ys = 1;
            }
                else
            {
               ys = 0;
            }
                }
                    else if (al->y > (24-THANOS_ALTURA))
                {
                    ys = -1;
            }

                if ( (al->x==0) || (al->x==69) )
            {
                xs = -xs;
            }

            al->y += ys;
            al->x += xs;

            if ( (al->y < 10) && (al->gemas > 0) && (rrand(1,100)>95) )
            {
                int n,i;
                n = fuego_gema(&(al->gemas));
            // Crea Gemas
                if (n>=0)
                {
                    todas_naves[n].tipo = AT_DIM;
                    //todas_naves[n].blit = blit_mini_nave;
                    //todas_naves[n].clear = limpiar_mini_nave;
                    for (i=0;i<MAX_ALT;i++)
                    todas_naves[n].collide[i] = bitmask_dim_nave[i];
                    todas_naves[n].estado = -1;
                    todas_naves[n].x = al->x+5;
                    todas_naves[n].y = al->y+5;
                    todas_naves[n].move = mover_nave_s;
                }
            }
                else if (rrand(1,100)>95)
            {
                tirar_gemas(&(al->gemas));
            }
        }
            else
        {
            int i;
            for (i=0;i<4;i++)
            {
                if (todas_naves[i].tipo==NV_NINGUNA)
                {
                    todas_naves[i].tipo=NV_GR_EXP;
                    todas_naves[i].estado=0;
                    todas_naves[i].blit=blit_explosion_3;
                    todas_naves[i].clear=limpiar_explosion_3;
                    todas_naves[i].x=rrand(al->x,al->x+9);
                    todas_naves[i].y=rrand(al->y,al->y+5);
                }
            }
        }
    }
}

void mover_titan()
{
    mover_thanos(&thanos);
}

/* Esta función calcula el elemento blitting adicional para Thanos
(guantelete y gemas) */
unsigned int thanos_extra(nave_titan *al)
{
    unsigned int ret=0;
    if (al->damage > (60*MAX_DAMAGE/100)) ret=COL_GREEN;
    else if (al->damage > (20*MAX_DAMAGE/100)) ret=COL_YELLOW;
    else ret=COL_RED;

    ret |= (al->gemas) << 8;

    return ret;
}

void blit_titan()
{
    if (thanos.habilitado)
    {
        thanos.blit(thanos.x+x_ofs,thanos.y+y_ofs,thanos_extra(&thanos));
    }
}

void elimina_titan()
{
    if (thanos.habilitado)
    {
    thanos.clear(thanos.x+x_ofs,thanos.y+y_ofs);
    }
}