#include <stdlib.h>

extern int term_x;
extern int term_y;
extern int x_ofs;
extern int y_ofs;

int rrand(int min, int max)
{
	return( min+(int) ((float)(max-min)*rand()/(RAND_MAX+1.0)) );
}

int es_y_rango(int y)
{
	return ((y>=y_ofs) && (y<term_y-y_ofs));
}

int es_x_rango(int x)
{
	return ((x>=x_ofs) && (x<term_x-x_ofs));
}