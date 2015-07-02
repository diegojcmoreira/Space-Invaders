#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "vidas.h"

void inicializa_vidas(Vidas* vidas)
{
	//vidas->posicao_x = ;
	vidas->posicao_y = POSICAO_Y_VIDA;
	inicializa_fonte(vidas);
	vidas->chances = N_VIDAS;
	vidas->vida_imagem = al_load_bitmap("imagens/vida.png");
}

void inicializa_fonte(Vidas* vidas)
{
	vidas->fonte = al_load_font("fontes/arcade.ttf", TAMANHO_FONTE, 0);
}

void finaliza_vidas(Vidas* vidas)
{
	al_destroy_font(vidas->fonte);
	al_destroy_bitmap(vidas->vida_imagem);
}

void desenha_vidas(Vidas* vidas)
{
	for (int i = 0; i < vidas->chances; i++)
	{
		desenha_chances(vidas, i);
	}
	 //al_draw_textf(vidas->fonte , al_map_rgba(VERDE_CLARO,100), DISPLAY_WIDTH -((DISPLAY_WIDTH/19)*(N_VIDAS +1)) + 10, POSICAO_Y_VIDA, ALLEGRO_ALIGN_RIGHT, "VIDAS");

}

void desenha_chances(Vidas* vidas, int i )
{

al_draw_scaled_bitmap(vidas->vida_imagem,
   0, 0, al_get_bitmap_width(vidas->vida_imagem), al_get_bitmap_height(vidas->vida_imagem),
    DISPLAY_WIDTH - ((DISPLAY_WIDTH/19) * (i+1)), 10, DISPLAY_WIDTH/19, DISPLAY_HEIGHT/10 , 0 );
}
