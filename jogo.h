#ifndef JOGO_H
#define JOGO_H

#include "bunker.h"
#include "spaceship.h"
#include "missil.h"
#include "alien.h"
#include "zbuffer.h"


enum TECLA { TECLA_ESQUERDA, TECLA_DIREITA, TECLA_ESC };


struct Jogo 
{
 
  int largura, altura;
  int N_MISSEIS;
  int N_DESTROYERS;
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *fila_eventos;
  Bunker bunker[N_BUNKERS];
  SPACESHIP spaceship;
  ALLEGRO_BITMAP* JANELA;
  ALLEGRO_TIMER* timer;
  Missil missil[MAX_MISSEIS];
  Alien alien[COLUNAS_TROPA][LINHAS_TROPA];
  ZBuffer zbuffer;
  bool esquerda;
};

void inicializa_jogo( Jogo* jogo, int largura, int altura);

void finaliza_jogo( Jogo* jogo );

void move_spaceship_jogo( Jogo* jogo, DIRECAO direcao );

void inicio(Jogo* jogo);

void desenha_jogo( Jogo* jogo );

void inicializa_timer_jogo (Jogo* jogo);

void inicializa_eventos (Jogo* jogo);

//void atirar(Jogo* jogo, SENTIDO sentido);

#endif
