#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "defs.h"
#include "blit.h"
#include "naves.h"
#include "thanos.h"
#include "niveles.h"
#include "fuego.h"
#include "escudo.h"

int puntaje = 0;
int final_x;
int juego_terminado = 0;
int x_ofs = 0;
int y_ofs = 0;
int term_x = 0;
int term_y = 0;

const bitmask bitmask_nave={0x38,0x7C,0xFE,0x7C,0x00};

WINDOW* term; // Mi terminal
int salud=15;
int explotamiento=0; // esto será> 0 si la nave del jugador está explotando

void pantalla_inicio()
{
	term = initscr(); // Inicializa la terminal

	start_color(); // Inicializa los colores
	init_pair(PC_WHITE,COLOR_WHITE,COLOR_BLACK);
	init_pair(PC_RED,COLOR_RED,COLOR_BLACK);
	init_pair(PC_GREEN,COLOR_GREEN,COLOR_BLACK);
	init_pair(PC_YELLOW,COLOR_YELLOW,COLOR_BLACK);
	init_pair(PC_BLUE,COLOR_BLUE,COLOR_BLACK);
	init_pair(PC_MAGENTA,COLOR_MAGENTA,COLOR_BLACK);
	init_pair(PC_CYAN,COLOR_CYAN,COLOR_BLACK);
	SET_COLOR(COL_BKG);


	nonl(); // No traducir retorno a línea nueva, solo CR
	intrflush(term,FALSE); // No vaciar la entrada en ^ C
	keypad(term,TRUE); // Habilitar teclado

	wrefresh(term);
}

// Retorna real si la terminal tiene tamaño de 80x25
int tam_derecho()
{
	getmaxyx(term,term_y,term_x);

	x_ofs = (term_x-80)/2;
	y_ofs = (term_y-25)/2;

	return ((term_x>=80)&&(term_y>=25));
}

void presentacion(char* str)
{

	blit_bordes(COLOR_BLACK);
	SET_COLOR(COL_MAGENTA);
	mvwprintw(term,8+y_ofs,25+x_ofs,"-- -= I-N-F-I-N-I-T-E  W-A-R =- --");
	mvwprintw(term,11+y_ofs,27+x_ofs,  "Salva al Planeta!!!");
	SET_COLOR(COL_WHITE);


	nodelay(term,FALSE);
	mvwprintw(term,20+y_ofs,29+x_ofs,    "Ingresa tu nombre de usuario: ");
	getstr(str);

	/*
	En esta parte lo que hice fue que me salia  ^ C cuando se salia del espacio de la terminal
	*/
	cbreak(); // Deshabilita el almacenamiento en búfer de línea y borra / elimina caracteres
	noecho(); // No reproduce caracteres
	nodelay(term,TRUE); // No bloquear mientras espera la entrada
	SET_COLOR(COL_DARKCYAN);
	mvwprintw(term,22+y_ofs,29+x_ofs,    "Presiona cualquier tecla para empezar");

	while (wgetch(term) == ERR)
	;

	wclear(term);

}

int pause()
{
	int overwritten[16];
	int ch,i;

	for (i=0;i<16;i++)
	overwritten[i] = (int)mvwinch(term,10,31+i);

	SET_COLOR(COL_RED);
	mvwprintw(term,10,31," * PAUSA * ");
	SET_COLOR(COL_BKG);

	wmove(term,0,0);

	while ((ch=wgetch(term)) == ERR)
	;

	for (i=0;i<16;i++)
	mvwaddch(term,10,31+i,(chtype)overwritten[i]);

	if ((ch==KEY_ESC) || (ch=='Q'))
	{
		return -1;
	}
	return 0;
}

int colision_nave(int x)
{
	int check_x,check_y;
	for (check_y=0; check_y<MAX_ALT; check_y++)
	{
		for (check_x=0; check_x<8; check_x++)
		{
			if ( (bitmask_nave[check_y] & (0x80 >> check_x)) != 0 )
			{
				if (colision_naves(x+check_x,21+check_y)>=0)

				return 1;
				if (colision_titan(x+check_x,21+check_y,COL_NAVE)>=0)
				return 1;
			}
		}
	}
	return 0;
}

int mover_nave()
{
	int c=0; // lee los caracteres
	static int ultima_c=-1;
	static int x=37; // posicion de la nave
	static int xs=0; // velocidad de la nave

	if (juego_terminado)
	{
		final_x=x; // Publico la nave en la posicion X
		return 0;
	}

	if (explotamiento == 0)
	{
		c = wgetch(term);
		if (c != ultima_c)
		{
			switch(c)
			{
				case ERR:
				// No mas teclas presionadas
				break;
				case KEY_LEFT:
				xs--;
				break;
				case KEY_RIGHT:
				xs++;
				break;
				case KEY_DOWN:
				xs=0;
				break;
				case ' ':
				case KEY_ENTER_:
				nuevo_fuego(x+3,21);
				break;
				case 's':
				case KEY_BACKSPACE:
				case KEY_UP:
				abrir_escudos(x-1,20);
				break;
				case 'p':
				case 'P':
				if (pause()<0)
				{
					c='Q';
				}
				break;
				case KEY_ESC:
				c='Q';
			}
		}
		ultima_c = c;

		// Chequea los limites
		if (xs>MAXRAPI) xs=MAXRAPI;
		if (xs<-MAXRAPI) xs=-MAXRAPI;

		limpiar_nave(x+x_ofs,21+y_ofs);

		x+=xs;

		if ( (x<0) || (x>73) )
		{
			xs = 0;
			(x>0)?(x=73):(x=0);
		}

		blit_nave(x+x_ofs,21+y_ofs);

		// Chequeo las colisiones con la naves
		if (colision_nave(x))
		{
			
			if (salud<6){
				explotamiento=1;
			}else{
				salud--;
			}
		}
	}
	else
	{
		switch (explotamiento++)
		{
			case 1:
			limpiar_nave(x+x_ofs,21+y_ofs);
			blit_explosion(x+3+x_ofs,22+y_ofs,3);
			break;
			case 2:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,3);
			blit_explosion(x+3+x_ofs,22+y_ofs,3);
			break;
			case 3:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,3);
			blit_explosion(x+3+x_ofs,22+y_ofs,4);
			break;
			case 4:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,4);
			blit_explosion(x+3+x_ofs,22+y_ofs,4);
			break;
			case 5:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,4);
			blit_explosion(x+3+x_ofs,22+y_ofs,3);
			break;
			case 6:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,3);
			blit_explosion(x+3+x_ofs,22+y_ofs,3);
			break;
			case 7:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,3);
			blit_explosion(x+3+x_ofs,22+y_ofs,2);
			break;
			case 8:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,2);
			blit_explosion(x+3+x_ofs,22+y_ofs,2);
			break;
			case 9:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,2);
			blit_explosion(x+3+x_ofs,22+y_ofs,1);
			break;
			case 10:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,1);
			blit_explosion(x+3+x_ofs,22+y_ofs,1);
			break;
			case 11:
			limpiar_explosion(x+3+x_ofs,22+y_ofs,1);
			c='Q';
			break;
		}
	}

	wmove(term,0,0);
	wrefresh(term);

	return (c!='Q');
}

void m_wait(long delay)
{
	usleep(delay);
}

void end_game()
{
	int y;
	for (y=21;y>-7;y--)
	{
		limpiar_nave(final_x+x_ofs,y+y_ofs);
		blit_nave(final_x+x_ofs,y-1+y_ofs);

		wmove(term,0,0);
		wrefresh(term);

		m_wait(DELAY);

		elimina_naves();
		elimina_titan();
		elimina_fuegos();
		limpia_escudos();

		movimiento_fuegos();
		mueve_naves();
		mover_titan();
		mover_escudos();

		blit_titan();
		blit_naves();
		blit_fuegos();
		blit_escudos();
		blit_puntaje(74+x_ofs,y_ofs,puntaje);
		blit_bordes(COL_RED);
	}
}

void final()
{
	printf("\n    FELICIDADES!\n");
	printf("    Haz derrotado a THANOS, el Titan más loco!\n\n");

	printf("    Con THANOS desaparecido, sus subditos huyeron con temor\n");
	printf("    buscando salvarse a sí mismos, y el ataque a la tierra falló.\n");
	printf("    2 años después, la raza alienigena fue completamente derrotada, y la\n");
	printf("    a raza humana quedo a salvo de morir con las gemas del infinito.\n");
	printf("    Los Avengers que mataron a THANOS fueron condecorados, y su valentía es\n");
	printf("    grabado en cada libro de historia. LOS AVENGERS LO LOGRARON!\n");
	printf("\n                               * El FINAL *\n");
}

void guardaHighScores(){
	FILE *archivo;
	archivo=fopen("h","w");
	fprintf(archivo,"hola");
	fclose(archivo);
}

void abreHighScores(){
	FILE* archivo;
	archivo=fopen("h","r");
	int caracter;
	char letra;
	char buffer[1000];

	int pos=0;
	do{
		caracter=fgetc(archivo);
		if(caracter!=EOF){
			letra=caracter;
			buffer[pos]=caracter;
		}
	}while(caracter!=EOF);

	FILE *archivo1;
	archivo1=fopen("h1","w");
	fprintf(archivo1,buffer);
	fclose(archivo1);

	fclose(archivo);
}
/*
void calculo(){
int puntos=0;;;
if (end_game==true)
{
puntos=puntos+1;
}
 FILE * f_mayor_puntuacion = NULL;
    f_mayor_puntuacion = fopen("record.txt","r");
    int recordactual=fscanf(f_mayor_puntuacion,"%d",&recordactual);
    fclose(f_mayor_puntuacion);
    if (puntos>recordactual)
    {
        f_mayor_puntuacion=fopen("record.txt","w");
        fprintf(f_mayor_puntuacion,"El record actual son %d puntos",puntos);
        fclose(f_mayor_puntuacion);
    }
}
*/
int main()
{
	abreHighScores();
	//calculo();
	srand(time(NULL));
	pantalla_inicio();

	if (!tam_derecho()){
		endwin();
		fprintf(stderr,"Galaga te pide un tamaño de 80x25 en tu terminal!\n");
		return -1;
	}

	char str[20];
	presentacion(str);

	inicia_naves();
	inicia_titan();
	inicia_niveles();
	inicia_fuegos();
	inicia_escudos();

	while (mover_nave())
	{
		m_wait(DELAY);

		elimina_naves();
		elimina_titan();
		elimina_fuegos();
		limpia_escudos();

		// mueve las funciones y también realiza la verificación de colisión
		movimiento_fuegos();
		mueve_naves();
		mover_titan();
		mover_escudos();

		blit_titan();
		blit_naves();
		blit_fuegos();
		blit_escudos();
		blit_puntaje(74+x_ofs,y_ofs,puntaje);
		blit_salud(x_ofs,y_ofs+1,salud/5);
		blit_bordes(COL_GREEN);
	}

	if (juego_terminado)
	{
		end_game();
	}

	// Entrada del juego
	while (wgetch(term) != ERR)
	;

	endwin();

	if (juego_terminado) final();


	printf("%s", str);
	printf(", tienes %d puntos!\n",puntaje);
	printf("-= INFINITE WAR =- Galaga! \n");
	guardaHighScores();
	return 0;
}
