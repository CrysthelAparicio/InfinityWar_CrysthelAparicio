#ifndef DEFS_H
#define DEFS_H

#ifndef NULL
#define NULL 0
#endif

#define MAXRAPI 3   // Velocidad maxima de la nave
#define DELAY 40000  // Afecta la velocidad del juego

#define KEY_ESC 033  // Tecla de escape para salida
#define KEY_ENTER_ 015  // Tecla de ENTER para iniciar el juego

// Colores 

#define PC_WHITE 1
#define PC_RED 2
#define PC_GREEN 3
#define PC_YELLOW 4
#define PC_BLUE 5
#define PC_MAGENTA 6
#define PC_CYAN 7
#define PC_PINK 8

#define SET_COLOR(x) wcolor_set(term,((x)>10)?((x)-10):(x),NULL); ((x)>10)?wattron(term,A_BOLD):wattroff(term,A_BOLD);

#define COL_GRAY          1
#define COL_DARKRED       2
#define COL_DARKGREEN     3
#define COL_DARKYELLOW    4
#define COL_DARKBLUE      5
#define COL_DARKMAGENTA   6
#define COL_DARKCYAN      7
#define COL_WHITE        11
#define COL_RED          12
#define COL_GREEN        13
#define COL_YELLOW       14
#define COL_BLUE         15
#define COL_MAGENTA      16
#define COL_CYAN         17
#define COL_ORANGE       21
#define COL_PINK         23

#define COL_BKG          COL_BLUE

#endif 
