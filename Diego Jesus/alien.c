#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "bunker.h"
#include "spaceship.h"
#include "buffer.h"
#include "missil.h"
#include "alien.h"

#define ALTURA_NAVE 40
#define LARGURA_NAVE 40

void inicializa_alien (Alien* alien, int posicao_x, int posicao_y) {
	alien->posicao_x = posicao_x;
	alien->posicao_y = posicao_y;
	puts("COMO EU PUDE FAZER ISSO ?");
	alien->min_x = alien->posicao_x - alien->delta_x; 
	alien->max_x = alien->posicao_x + alien->delta_x;

	alien->vivo = true;
	puts("ENTROU NO inicializa_alien");
	inicializa_sprites_alien (alien);
	puts("O ERRO É AQUI");
	alien->delta_x = al_get_bitmap_width(alien->IMAGEM)/2;
}

void inicializa_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], int posicao_x, int posicao_y) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			inicializa_alien (&alien[i][j], posicao_x + i * (LARGURA_NAVE + LARGURA_NAVE/2),
									posicao_y + j * (ALTURA_NAVE + ALTURA_NAVE/2) ); 

}

void finaliza_alien (Alien* alien) {
	finaliza_sprites_alien(alien);
}

void desenha_alien (Alien* alien) 
{
	puts("ENTROU AQUI");
	int flags = 0;

	al_draw_bitmap (alien->IMAGEM, 
					alien->posicao_x - alien->delta_x, 
					alien->posicao_y,
					flags);
}

void desenha_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA]) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			if (alien[i][j].vivo)
				desenha_alien (&alien[i][j]);
}

void inicializa_sprites_alien (Alien* alien) 
{
	puts("ENTROU NO inicializa_sprites_alien");
	alien->IMAGEM = al_load_bitmap("imagens/DESTROYER.png");

	if (alien->IMAGEM == NULL) 
	{
		puts("Erro ao carregar o arquivo imagens/DESTROYER.png");
		exit(0);
	}
}

void finaliza_sprites_alien (Alien* alien) 
{
	al_destroy_bitmap(alien->IMAGEM);
}

void move_alien (Alien* alien, DIRECAO direcao) 
{
	if (direcao == ESQUERDA)
		alien->posicao_x -= DISTANCIA_PASSO;
	
	if (direcao == DIREITA)
		alien->posicao_x += DISTANCIA_PASSO;
}
