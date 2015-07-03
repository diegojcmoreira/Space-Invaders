#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "bunker.h"
#include "spaceship.h"
#include "missil.h"
#include "inimigo.h"
#include "zbuffer.h"
#include "define.h"



void inicializa_inimigo (Inimigo* inimigo, int posicao_x, int posicao_y) {
	inimigo->posicao_x = posicao_x;
	inimigo->posicao_y = posicao_y;
	
	
	
	inimigo->direcao_atual = ESQUERDA;
	inimigo->vivo = true;
	inicializa_bitmap_inimigo (inimigo);
	inimigo->altura = DISPLAY_WIDTH/19;
	inimigo->largura = DISPLAY_HEIGHT/10;
	inimigo->max_y = inimigo->posicao_y + (inimigo->altura);
	inimigo->min_y = inimigo->posicao_y - (inimigo->altura);
	inimigo->min_x = inimigo->posicao_x - (inimigo->largura); 
	inimigo->max_x = inimigo->posicao_x + (inimigo->largura);
	
}

void inicializa_tropa (Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA], int posicao_x, int posicao_y) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			inicializa_inimigo (&inimigo[i][j], posicao_x + (1.3 * i) * (LARGURA_NAVE + LARGURA_NAVE/2),
									posicao_y + (1.3 * j) * (ALTURA_NAVE + ALTURA_NAVE/2) ); 

}

void finaliza_inimigo ( Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA]) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			finaliza_bitmap_inimigo(&inimigo[i][j]);
}

void desenha_inimigo (Inimigo* inimigo) 
{

al_draw_scaled_bitmap(inimigo->IMAGEM,
   0, 0, al_get_bitmap_width(inimigo->IMAGEM), al_get_bitmap_height(inimigo->IMAGEM),
   inimigo->posicao_x, inimigo->posicao_y, DISPLAY_WIDTH/19, DISPLAY_HEIGHT/9 , 0 );

	
}

void desenha_tropa (Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA]) {
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			if (inimigo[i][j].vivo)
				desenha_inimigo (&inimigo[i][j]);
}

void inicializa_bitmap_inimigo (Inimigo* inimigo) 
{
	inimigo->IMAGEM = al_load_bitmap("imagens/DESTROYER3.png");

	if (inimigo->IMAGEM == NULL) 
	{
		puts("Erro ao carregar o arquivo imagens/DESTROYER.png");
		exit(0);
	}
}

void finaliza_bitmap_inimigo (Inimigo* inimigo) 
{
	al_destroy_bitmap(inimigo->IMAGEM);
}

void move_inimigos (Inimigo* inimigo, DIRECAO direcao) 
{
	if (direcao == ESQUERDA) 
		inimigo->posicao_x -= DISTANCIA_PASSO;			
	
	if (direcao == DIREITA)	
		inimigo->posicao_x += DISTANCIA_PASSO;

	inimigo->min_x = inimigo->posicao_x - (inimigo->largura); 
	inimigo->max_x = inimigo->posicao_x + (inimigo->largura);
}

void move_comboio (Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA], DIRECAO direcao)
{

	if (direcao == ESQUERDA)
		for(int i = 0; i < COLUNAS_TROPA ; i++ )
			for(int j = 0; j < LINHAS_TROPA ; j++ )
				move_inimigos(&inimigo[i][j], direcao);
	
	if (direcao == DIREITA)
		for(int i = 0; i < COLUNAS_TROPA ; i++ )
			for(int j = 0; j < LINHAS_TROPA ; j++ )
				move_inimigos(&inimigo[i][j], direcao);

}

void move_inimigo_sentido (Inimigo* inimigo, SENTIDO sentido)
{
	if (sentido == BAIXO) 
		inimigo->posicao_y += 10;

	if (sentido == CIMA) 
		inimigo->posicao_y -= 10;

	inimigo->max_y = inimigo->posicao_y + (inimigo->altura);
	inimigo->min_y = inimigo->posicao_y - (inimigo->altura);
}

void move_comboio_baixo(Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA])
{

	for(int i = 0; i < COLUNAS_TROPA; i++ )
		for(int j = 0; j < LINHAS_TROPA; j++ )
			move_inimigo_sentido(&inimigo[i][j], BAIXO);

			
}

void automatizacao_inimigo( Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA])
{
	if(inimigo[0][0].direcao_atual == ESQUERDA)
		if (inimigo[0][0].posicao_x > 0 )
	  	{

		    move_comboio (inimigo, ESQUERDA);
		    desenha_tropa(inimigo);
	  	}
	  	else
  		inverte_direcao(inimigo, DIREITA);
	
	if(inimigo[0][0].direcao_atual == DIREITA)
	  	if (inimigo[COLUNAS_TROPA - 1][LINHAS_TROPA - 1].posicao_x < DISPLAY_WIDTH - inimigo[COLUNAS_TROPA - 1][LINHAS_TROPA - 1].largura)
	  	{
			move_comboio (inimigo, DIREITA);
	    	desenha_tropa(inimigo); 
	  	}
	  	else
	  		inverte_direcao(inimigo, ESQUERDA);

}

void inverte_direcao(Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA], DIRECAO direcao)
{
	move_comboio_baixo(inimigo);
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			inimigo[i][j].direcao_atual = direcao;

	
}

void atira_comboio (Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA], Missil* missil) 
{
    srand(time(NULL));
    int quem_atira_x = rand() % COLUNAS_TROPA;
    int quem_atira_y = LINHAS_TROPA-1;

    for (int i = 0; i < COLUNAS_TROPA; ++i)
     if (!inimigo[quem_atira_x][0].vivo)
        quem_atira_x = (quem_atira_x+1) % COLUNAS_TROPA;


    while (!inimigo[quem_atira_x][quem_atira_y].vivo && quem_atira_y > 0)
        quem_atira_y--;

    inicializa_missil_inimigo(missil, (inimigo[quem_atira_x][quem_atira_y].posicao_x + (inimigo[quem_atira_x][quem_atira_y].largura/2)) - missil->largura,
                                inimigo[quem_atira_x][quem_atira_y].posicao_y + inimigo[0][0].altura, BAIXO); 
}

bool inimigo_vivo(Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA])
{
	for (int i = 0; i < COLUNAS_TROPA; i++)
		for (int j = 0; j < LINHAS_TROPA; j++)
			if(inimigo[i][j].vivo)
				return true;

}
