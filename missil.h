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
  	SENTIDO sentido;
	ALLEGRO_BITMAP* bitmap;
};

void inicializa_missil( Missil* missil, int x, int y, SENTIDO sentido );

void finaliza_missil( Missil* missil );

void desenha_missil( Missil* missil );

void move_missil( Missil* missil, SENTIDO direcao );

void copiar_missil (Missil* destino, Missil* origem);

void inicializa_missil_alien( Missil* missil, int posicao_x, int y, SENTIDO sentido );


#endif

