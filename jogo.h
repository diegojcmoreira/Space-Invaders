#ifndef JOGO_H
#define JOGO_H

#include "bunker.h"
#include "spaceship.h"
#include "missil.h"
#include "alien.h"
#include "zbuffer.h"
#include "define.h"


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
  ALLEGRO_BITMAP* TELA_INICIAL;
  Missil missil[MAX_MISSEIS];
  Alien alien[COLUNAS_TROPA][LINHAS_TROPA];
  ZBuffer zbuffer;
  bool esquerda;
  bool pause;
  int tempo;
};

void inicializa_jogo( Jogo* jogo, int largura, int altura);

void finaliza_jogo( Jogo* jogo );

void move_spaceship_jogo( Jogo* jogo, DIRECAO direcao );

void inicio(Jogo* jogo);

void desenha_jogo( Jogo* jogo );

void inicializa_timer_jogo (Jogo* jogo);

void inicializa_eventos (Jogo* jogo);

void colisao (Jogo* jogo );

void colisao_missil_spaceship (Jogo* jogo, Bunker* bunker);

void menu(Jogo* jogo);

void inicializar_fundo_allegro(Jogo* jogo);

void inicializar_display(Jogo* jogo);

void inicializar_imagem_allegro();

void inicializar_fontes_allegro();

void inicializar_teclado_allegro();

void inicializa_primitivas_allegro();

void inicializar_allegro();

void inicializar_todo_allegro();

void inicializar_fundo(Jogo* jogo);

void inicializar_tela_inicial(Jogo* jogo);

void tela_inicial (Jogo* jogo);

void colisao (Jogo* jogo, int teste);


//void atirar(Jogo* jogo, SENTIDO sentido);

#endif
