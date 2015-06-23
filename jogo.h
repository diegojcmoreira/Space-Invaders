// O Jogo Space Invaders
// Autor: GZS

#ifndef JOGO_H
#define JOGO_H

#define FUNDO al_map_rgb(0, 0, 0)

#include "bunker.h"
#include "tanque.h"

struct Jogo {
  int largura, altura; 
  ALLEGRO_DISPLAY *display;
  Bunker bunker[4];
  Tanque tanque;
  ALLEGRO_BITMAP* JANELA;
};

void inicializa_jogo( Jogo* jogo, int largura, int altura);

void finaliza_jogo( Jogo* jogo );

void desenha_jogo( Jogo* jogo );

void move_tanque_jogo( Jogo*, DIRECAO direcao );

void inicio(Jogo* jogo);

#endif
