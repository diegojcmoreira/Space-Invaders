#ifndef Missil_H
#define Missil_H

enum SENTIDO { CIMA, BAIXO };

struct Missil
{
	int posicao_x;
	int posicao_y;
  	int DELTA_Y;
  	SENTIDO sentido;
	ALLEGRO_BITMAP* bitmap;
};

void inicializa_missil( Missil* missil, int x, int y, SENTIDO sentido );

void finaliza_missil( Missil* missil );

void desenha_missil( Missil* missil );

void move_missil( Missil* missil, SENTIDO direcao );

#endif

