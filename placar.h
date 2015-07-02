#ifndef PLACAR_H
#define PLACAR_H

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "define.h"


struct Placar
{
	int posicao_x, posicao_y, pontuacao;
	ALLEGRO_FONT* fonte;
};

void inicializa_placar(Placar* placar);

void desenha_placar(Placar* placar);

void finaliza_placar(Placar* placar);

void inicializa_fonte (Placar* placar);


#endif

