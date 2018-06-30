#ifndef BLIT_H
#define BLIT_H

void blit_explosion_1(int,int);
void blit_explosion_2(int,int);
void blit_explosion_3(int,int);
void blit_explosion_4(int,int);

void limpiar_explosion_1(int,int);
void limpiar_explosion_2(int,int);
void limpiar_explosion_3(int,int);
void limpiar_explosion_4(int,int);

void blit_explosion(int,int,int);
void limpiar_explosion(int,int,int);

void blit_grande_nave(int,int);
void limpiar_grande_nave(int,int);

void blit_peque_nave(int,int);
void limpiar_peque_nave(int,int);

void blit_bola_nave(int x,int y);
void limpiar_bola_nave(int x,int y);

void blit_limo_nave(int x,int y);
void limpiar_limo_nave(int x,int y);

void blit_mini_nave(int x,int y);
void limpiar_mini_nave(int x,int y);

void blit_fuego(int,int);
void limpiar_fuego(int,int);

void blit_nave(int,int);
void limpiar_nave(int,int);

void blit_dark(int,int);
void limpiar_dark(int,int);

void blit_escudo(int,int,int);
void blit_escudo_carga(int,int,int);
void limpiar_escudo(int,int);
void limpiar_escudo_carga(int,int);

void blit_puntaje(int,int,int);

void blit_thanos(int,int,int);
void limpiar_thanos(int,int);

void blit_bordes(int);

#endif 
