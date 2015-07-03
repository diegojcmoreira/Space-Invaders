#ifndef Missil_H
#define Missil_H

#include "define.h"

struct Missil
{
	int posicao_x;
	int posicao_y;
  	int altura;
  	int velocidade;
  	int largura;
  	int misseis_ativos;
  	SENTIDO sentido;
	ALLEGRO_BITMAP* bitmap;
};

void inicializa_missil( Missil* missil, int x, int y, SENTIDO sentido );

void finaliza_missil( Missil* missil );

void desenha_missil( Missil* missil );

void move_missil( Missil* missil, SENTIDO direcao );

void copiar_missil (Missil* destino, Missil* origem);

void inicializa_missil_inimigo( Missil* missil, int posicao_x, int y, SENTIDO sentido );

void finaliza_missil( Missil* missil );

void inicializa_imagem_missil(Missil* missil);


#endif

