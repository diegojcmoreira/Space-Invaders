#include "placar.h"

void inicializa_placar(Placar* placar)
{
	placar->posicao_x = POSICAO_X_PLACAR;
	placar->posicao_y = POSICAO_Y_PLACAR;
	inicializa_fonte(placar);

	placar->pontuacao = 0;

}

void desenha_placar(Placar* placar)
{
	al_draw_textf(placar->fonte , al_map_rgba(VERDE_CLARO,100), POSICAO_X_PLACAR, POSICAO_Y_PLACAR, ALLEGRO_ALIGN_LEFT, "%d", placar->pontuacao);

}

void finaliza_placar(Placar* placar)
{
	al_destroy_font(placar->fonte);
}


void inicializa_fonte (Placar* placar)
{
	placar->fonte = al_load_font("fontes/arcade.ttf", TAMANHO_FONTE, 0);
	 if (!placar->fonte)
    {
        fprintf(stderr, "Falha ao carregar fonte.\n");
        exit(-1);
    }
}