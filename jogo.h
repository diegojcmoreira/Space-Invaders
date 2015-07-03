#ifndef JOGO_H
#define JOGO_H



#include "bunker.h"
#include "placar.h"
#include "spaceship.h"
#include "missil.h"
#include "inimigo.h"
#include "zbuffer.h"
#include "define.h"
#include "vidas.h"
#include "death_star.h"



enum TECLA { TECLA_ESQUERDA, TECLA_DIREITA, TECLA_ESC };


struct Jogo 
{
 
  int largura, altura;
  Vidas vidas;
  Placar placar;
  int N_MISSEIS;
  int vida;
  int misseis_ativos_spaceship;
  int ativar_death_star;
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *fila_eventos, *apos_perder;
  Bunker bunker[N_BUNKERS];
  SPACESHIP spaceship;
  ALLEGRO_BITMAP* JANELA;
  ALLEGRO_BITMAP* vida_imagem;
  ALLEGRO_TIMER* timer;
  ALLEGRO_BITMAP* TELA_INICIAL;
  Missil missil[MAX_MISSEIS];
  Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA];
  ZBuffer zbuffer;
  bool saida;
  Death_star death_star;
  ALLEGRO_FONT* fonte;
  
};

void inicializa_jogo( Jogo* jogo, int largura, int altura);

void finaliza_jogo( Jogo* jogo );

void move_spaceship_jogo( Jogo* jogo, DIRECAO direcao );

void inicio(Jogo* jogo);

void desenha_jogo( Jogo* jogo );

void inicializa_timer_jogo (Jogo* jogo);

void inicializa_eventos (Jogo* jogo);

void colisao_missil_bunker (Jogo* jogo, Bunker* bunker);

void menu(Jogo* jogo);

void desenha_fundo(Jogo* jogo);

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

void colisao (Jogo* jogo, COLISAO colisao);

void colisao_death_star(Jogo* jogo);

void perdeu_vida(Jogo* jogo);

void fundo_pause (Jogo* jogo);

void inicializar_fontes_menu_pause (Jogo* jogo);

void perdendo_para_maquina(Jogo* jogo);

void winner (Jogo* jogo);

#endif
