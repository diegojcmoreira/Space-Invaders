#ifndef DEATH_STAR_H
#define DEATH_STAR_H

#include <stdio.h>
#include <stdlib.h>

#include "define.h"

struct Death_star
{
	int min_x, max_x, min_y, max_y;
	int posicao_x, posicao_y;
	int largura;
	int altura;
	bool movimento_death_star;
	ALLEGRO_BITMAP* IMAGEM;
};

void inicializa_death_star (Death_star* death_star, int posicao_x, int posicao_y);

void desenha_death_star (Death_star* death_star);

void move_death_star (Death_star* death_star, DIRECAO direcao);

void finaliza_death_star (Death_star* death_star);

void inicializa_imagem_death_star (Death_star* death_star);

void automatiza_death_star (Death_star* death_star);

void reinicializar_death_star (Death_star* death_star);



#endif
