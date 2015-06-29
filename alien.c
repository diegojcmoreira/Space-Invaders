#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "bunker.h"
#include "spaceship.h"
#include "missil.h"
#include "alien.h"
#include "zbuffer.h"

#define ALTURA_NAVE 40
#define LARGURA_NAVE 40

void inicializa_alien (Alien* alien, int posicao_x, int posicao_y) {
	alien->posicao_x = posicao_x;
	alien->posicao_y = posicao_y;
	
	alien->min_x = alien->posicao_x - alien->delta_x; 
	alien->max_x = alien->posicao_x + alien->delta_x;
	alien->direcao_atual = ESQUERDA;
<<<<<<< HEAD
	alien->max_y = posicao_y - alien->altura;
	alien->min_y = posicao_y + alien->altura;
=======

>>>>>>> 71c91122ae6b594b78375ef6c3904cb8773164a9
	alien->vivo = true;
	inicializa_sprites_alien (alien);
	alien->altura = al_get_bitmap_height(alien->IMAGEM);
	alien->delta_x = al_get_bitmap_width(alien->IMAGEM);
	
}

void inicializa_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], int posicao_x, int posicao_y) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			inicializa_alien (&alien[i][j], posicao_x + i * (LARGURA_NAVE + LARGURA_NAVE/2),
									posicao_y + j * (ALTURA_NAVE + ALTURA_NAVE/2) ); 
	printf("posição x no começo:%d\n", alien[0][0].posicao_x );

}

void finaliza_alien (Alien* alien) {
	finaliza_sprites_alien(alien);
}

void desenha_alien (Alien* alien) 
{

	int flags = 0;

	al_draw_bitmap (alien->IMAGEM, 
					alien->posicao_x, //(alien->delta_x * COLUNAS_TROPA), 
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
	//puts("ENTROU NO inicializa_sprites_alien");
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

void move_aliens (Alien* alien, DIRECAO direcao) 
{
	if (direcao == ESQUERDA)
		alien->posicao_x -= DISTANCIA_PASSO;
			
	
	if (direcao == DIREITA)
		alien->posicao_x += DISTANCIA_PASSO;
}

void move_comboio (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], DIRECAO direcao)
{

	if (direcao == ESQUERDA)
		for(int i = 0; i < COLUNAS_TROPA; i++ )
			for(int j = 0; j < LINHAS_TROPA; j++ )
				move_aliens(&alien[i][j], direcao);
	
	if (direcao == DIREITA)
		for(int i = 0; i < COLUNAS_TROPA; i++ )
			for(int j = 0; j < LINHAS_TROPA; j++ )
				move_aliens(&alien[i][j], direcao);

}

void move_aliens_baixo(Alien alien[COLUNAS_TROPA][LINHAS_TROPA])
{
	for(int i = 0; i < COLUNAS_TROPA; i++ )
		for(int j = 0; j < LINHAS_TROPA; j++ )
			alien[i][j].posicao_y += 10;	
}

void automatizacao_alien( Alien alien[COLUNAS_TROPA][LINHAS_TROPA])
{
	if(alien[0][0].direcao_atual == ESQUERDA)
		if (alien[0][0].posicao_x > -20 )
	  	{
		    move_comboio (alien, ESQUERDA);
		    desenha_tropa(alien);
	  	}
	  	else
	  		inverte_direcao(alien, DIREITA);
	
	if(alien[0][0].direcao_atual == DIREITA)
	  	if (alien[LINHAS_TROPA -1 ][LINHAS_TROPA - 1].posicao_x < 630)
	  	{
			move_comboio (alien, DIREITA);
	    	desenha_tropa(alien); 
	  	}
	  	else
	  		inverte_direcao(alien, ESQUERDA);
  	//printf("15");

}

void inverte_direcao(Alien alien[COLUNAS_TROPA][LINHAS_TROPA], DIRECAO direcao)
{
	move_aliens_baixo(alien);
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			alien[i][j].direcao_atual = direcao;

	
}
<<<<<<< HEAD

void atira_tropa (Alien alien[COLUNAS_TROPA][LINHAS_TROPA], Missil* projetil) 
{
    srand(time(NULL));
    int quem_atira_x = rand() % COLUNAS_TROPA;
    int quem_atira_y = LINHAS_TROPA-1;

    while (!alien[quem_atira_x][0].vivo)
        quem_atira_x = (quem_atira_x+1) % COLUNAS_TROPA;

    while (!alien[quem_atira_x][quem_atira_y].vivo && quem_atira_y > 0)
        quem_atira_y--;
    puts("ENTROU NO ATIRA TROPA");

    inicializa_missil (projetil, alien[quem_atira_x][quem_atira_y].posicao_x + alien[quem_atira_x][quem_atira_y].delta_x,
                                alien[quem_atira_x][quem_atira_y].posicao_y + alien[0][0].altura, BAIXO); 

}
=======
>>>>>>> 71c91122ae6b594b78375ef6c3904cb8773164a9
