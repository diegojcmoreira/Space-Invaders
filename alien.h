#ifndef ALIEN_H
#define ALIEN_H

#include <stdio.h>
#include <stdlib.h>

#define LINHAS_TROPA 5
#define COLUNAS_TROPA 6
#define DISTANCIA_PASSO 5

struct Alien 
{

	int min_x, max_x, min_y, max_y;
	int posicao_x, posicao_y;
	int delta_x;
	bool vivo;
	ALLEGRO_BITMAP* IMAGEM;
};

void inicializa_alien (Alien* alien, int posicao_x, int posicao_y);

void inicializa_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], int posicao_x, int posicao_y);

void finaliza_alien (Alien* alien);

void desenha_alien (Alien* alien);

void desenha_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA]);

void inicializa_sprites_alien (Alien* alien);

void finaliza_sprites_alien (Alien* alien);

void move_alien (Alien* alien, DIRECAO direcao);

#endif
