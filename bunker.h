
#ifndef BUNKER_H
#define BUNKER_H

#include "define.h"

#define TAMANHO_BUNKER (8*10)


struct Bunker {
  int posicao_x, posicao_y;
  int largura, altura;
  ALLEGRO_BITMAP* bunker_inteiro;
  ALLEGRO_BITMAP* bunker_fudido;  
  EstadoBunker pedaco[PEDACOS_LARGURA][PEDACOS_ALTURA];
};

void inicializa_bunker( Bunker *bunker, int posicao_x, int posicao_y );

void finaliza_bunker( Bunker *bunker );

void desenha_bunker( Bunker* bunker );

void desenha_imagem_bunker (Bunker* bunker);

#endif