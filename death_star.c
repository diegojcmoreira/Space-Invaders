#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "bunker.h"
#include "spaceship.h"
#include "missil.h"
#include "death_star.h"

void inicializa_death_star (Death_star* death_star, int posicao_x, int posicao_y) {
	
	death_star->posicao_x = posicao_x;
	death_star->posicao_y = posicao_y;
	inicializa_imagem_death_star(death_star);
	death_star->movimento_death_star = false;
	
	death_star->altura = DISPLAY_HEIGHT/9;
	death_star->largura = DISPLAY_WIDTH/19;
	
	death_star->max_y = death_star->posicao_y + (death_star->altura);
	death_star->min_y = death_star->posicao_y - (death_star->altura);
	death_star->min_x = death_star->posicao_x - (death_star->largura); 
	death_star->max_x = death_star->posicao_x + (death_star->largura);
}	

void inicializa_imagem_death_star (Death_star* death_star)
{
	death_star->IMAGEM = al_load_bitmap("imagens/death_star.png");
	 if( death_star->IMAGEM == NULL) 
  {
    puts( "Erro ao carregar o arquivo imagens/tank.png");
    exit(0);
  }
}

void desenha_death_star (Death_star* death_star) {
	al_draw_scaled_bitmap(death_star->IMAGEM,
   0, 0, al_get_bitmap_width(death_star->IMAGEM), al_get_bitmap_height(death_star->IMAGEM),
   death_star->posicao_x, death_star->posicao_y, DISPLAY_WIDTH/19, DISPLAY_HEIGHT/9 , 0 );
}

void move_death_star (Death_star* death_star, DIRECAO direcao) 
{
	if(direcao == DIREITA)
	{
		death_star->posicao_x += PASSO_DEATH_STAR;
		desenha_death_star(death_star);
	}

	if(direcao == ESQUERDA)
	{
		death_star->posicao_x -= PASSO_DEATH_STAR;
		desenha_death_star(death_star);
	}

}

void finaliza_death_star (Death_star* death_star) {
	al_destroy_bitmap(death_star->IMAGEM);
}

void automatiza_death_star (Death_star* death_star)
{
	if (death_star->posicao_x < DISPLAY_WIDTH + 1){
	move_death_star(death_star, DIREITA);
	}

	if (death_star->posicao_x > DISPLAY_WIDTH )
	{
		reinicializar_death_star (death_star);
	}
}

void reinicializar_death_star (Death_star* death_star)
{
	death_star->posicao_x = 0;
	death_star->max_y = death_star->posicao_y + (death_star->altura);
	death_star->min_y = death_star->posicao_y - (death_star->altura);
	death_star->min_x = death_star->posicao_x - (death_star->largura); 
	death_star->max_x = death_star->posicao_x + (death_star->largura);
	death_star->movimento_death_star = false;

}