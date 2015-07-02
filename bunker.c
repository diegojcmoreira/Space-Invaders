#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "jogo.h"
#include "bunker.h"

void inicializa_bunker (Bunker* bunker, int posicao_x, int posicao_y) {

  bunker->bunker_inteiro = al_load_bitmap("imagens/bunker2.png");
  if (bunker->bunker_inteiro == NULL) {
    fprintf(stderr, "Falha ao carregar o arquivo de imagem.\n");
       exit(-1);
  }

  bunker->bunker_fudido = al_load_bitmap("imagens/bunker2_fudido.png");
  if (bunker->bunker_fudido == NULL) {
   fprintf(stderr, "Falha ao carregar o arquivo de imagem.\n");
       exit(-1);
  }

  bunker->posicao_x = posicao_x;
  bunker->posicao_y = posicao_y;
  bunker->altura = al_get_bitmap_height(bunker->bunker_inteiro);
  bunker->largura = al_get_bitmap_width(bunker->bunker_inteiro);

  for (int i = 0; i < PEDACOS_LARGURA; i++) {
    for (int j = 0; j < PEDACOS_ALTURA; j++) {
      bunker->pedaco[i][j] = INTEIRO;
    }
  } 
}

void finaliza_bunker( Bunker *bunker ) {
}

void desenha_bunker( Bunker* bunker ) 
{	     
  for (int i = 0; i < PEDACOS_LARGURA; i++) 
    for (int j = 0; j < PEDACOS_ALTURA; j++) 
      if (bunker->pedaco[i][j] == INTEIRO) 

          al_draw_bitmap_region(bunker->bunker_inteiro,
                     (bunker->largura/ PEDACOS_LARGURA)*i,
                     (bunker->altura/ PEDACOS_ALTURA)*j,
                     (bunker->largura/ PEDACOS_LARGURA),
                     (bunker->altura/ PEDACOS_ALTURA),
                     bunker->posicao_x + (bunker->largura/ PEDACOS_LARGURA)*i, 
                     bunker->posicao_y + (bunker->altura/ PEDACOS_ALTURA)*j, 
                     0);
  
  for (int i = 0; i < PEDACOS_LARGURA; i++) 
    for (int j = 0; j < PEDACOS_ALTURA; j++) 
      if (bunker->pedaco[i][j] == AVARIADO) 
        al_draw_bitmap_region(bunker->bunker_fudido,
                     (bunker->largura/ PEDACOS_LARGURA)*i,
                     (bunker->altura/ PEDACOS_ALTURA)*j,
                     (bunker->largura/ PEDACOS_LARGURA),
                     (bunker->altura/ PEDACOS_ALTURA),
                     bunker->posicao_x + (bunker->largura/ PEDACOS_LARGURA)*i, 
                     bunker->posicao_y + (bunker->altura/ PEDACOS_ALTURA)*j, 
                     0);
      
}