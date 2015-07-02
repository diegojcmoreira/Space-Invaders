#ifndef VIDAS_H
#define VIDAS_H

#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "define.h"

struct Vidas
{
	int posicao_x, posicao_y, chances;
	ALLEGRO_BITMAP* vida_imagem;
	ALLEGRO_FONT* fonte;
	
};

void inicializa_vidas(Vidas* vidas);

void inicializa_fonte(Vidas* vidas);

void finaliza_vidas(Vidas* vidas);

void desenha_vidas(Vidas* vidas);

void desenha_chances(Vidas* vidas, int i );

#endif




