#ifndef INIMIGO_H
#define INIMIGO_H

#include <stdio.h>
#include <stdlib.h>

#include "define.h"

struct Inimigo 
{

	int min_x, max_x, min_y, max_y;
	int posicao_x, posicao_y;
	int largura;
	int altura;
	bool vivo;
	bool sentido;
	DIRECAO direcao_atual;
	ALLEGRO_BITMAP* IMAGEM;
};

void inicializa_inimigo (Inimigo* inimigo, int posicao_x, int posicao_y);

void inicializa_tropa (Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA], int posicao_x, int posicao_y);

void finaliza_inimigo (Inimigo* inimigo);

void desenha_inimigo (Inimigo* inimigo);

void desenha_tropa (Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA]);

void inicializa_bitmap_inimigo (Inimigo* inimigo);

void finaliza_bitmap_inimigo (Inimigo* inimigo);

void move_inimigos (Inimigo* inimigo, DIRECAO direcao);

void move_inimigo_sentido (Inimigo* inimigo, SENTIDO sentido);

void move_comboio_baixo(Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA]);

void automatizacao_inimigo( Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA]);

void move_comboio (Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA], DIRECAO direcao);

void inverte_direcao(Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA], DIRECAO direcao);

void atira_comboio (Inimigo inimigo[COLUNAS_TROPA][LINHAS_TROPA], Missil* projetil);


#endif
