// Bunker
// Autor: GZS

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "jogo.h"
#include "bunker.h"

void inicializa_bunker( Bunker *bunker, int posicao_x, int posicao_y ) {
  bunker->posicao_x = posicao_x;
  bunker->posicao_y = posicao_y;
  
  for( int i = 0; i < 8; i++ ) 
    for( int j = 0; j < 4; j++ ) {
      bunker->pedaco[i][j] = INTEIRO;
      bunker->desenho[i][j] = QUADRADO;
    }
       
  bunker->desenho[0][0] = INFERIOR_DIREITO;    
  bunker->desenho[7][0] = INFERIOR_ESQUERDO;    
  bunker->desenho[2][2] = SUPERIOR_ESQUERDO;    
  bunker->desenho[5][2] = SUPERIOR_DIREITO;    
  bunker->desenho[2][3] = VAZIO;    
  bunker->desenho[3][3] = VAZIO;    
  bunker->desenho[3][2] = VAZIO;    
  bunker->desenho[4][3] = VAZIO;    
  bunker->desenho[4][2] = VAZIO;    
  bunker->desenho[5][3] = VAZIO;     
}  

void finaliza_bunker( Bunker *bunker ) {
}

void desenha_pedaco_bunker( int x, int y, LegoBunker lego, EstadoBunker estado ) {	     
  switch( lego ) {
    case VAZIO:
          NULL;
         break;
    
    case QUADRADO:
          ALLEGRO_BITMAP* QUADRADO;
          QUADRADO = al_load_bitmap("QUADRADO.png");
          al_draw_bitmap(QUADRADO, x, y, 0);
         break;
    
    case INFERIOR_DIREITO:
           ALLEGRO_BITMAP* INFERIOR_DIREITO;
          INFERIOR_DIREITO = al_load_bitmap("INFERIOR_DIREITO.png");
          al_draw_bitmap(INFERIOR_DIREITO, x, y, 0);
         break;

    case INFERIOR_ESQUERDO:
           ALLEGRO_BITMAP* INFERIOR_ESQUERDO;
          INFERIOR_ESQUERDO = al_load_bitmap("INFERIOR_ESQUERDO.png");
          al_draw_bitmap(INFERIOR_ESQUERDO, x, y, 0);
         break;
    
    case SUPERIOR_ESQUERDO:
           ALLEGRO_BITMAP* SUPERIOR_ESQUERDO;
          SUPERIOR_ESQUERDO = al_load_bitmap("SUPERIOR_ESQUERDO.png");
          al_draw_bitmap(SUPERIOR_ESQUERDO, x, y, 0);
         break;
    
    case SUPERIOR_DIREITO:
          ALLEGRO_BITMAP* SUPERIOR_DIREITO;
          SUPERIOR_DIREITO = al_load_bitmap("SUPERIOR_DIREITO.png");
          al_draw_bitmap(SUPERIOR_DIREITO, x, y, 0);
         break;
    
  }
}
  
void desenha_bunker( Bunker* bunker ) {
  for( int i = 0, x = bunker->posicao_x; 
       i < 8; 
       i++, x += TAMANHO_BUNKER / 8 )
    for( int j = 0, y = bunker->posicao_y; 
         j < 4; 
         j++, y += TAMANHO_BUNKER / 8 ) {
             
      desenha_pedaco_bunker( x, y, bunker->desenho[i][j], bunker->pedaco[i][j] );     
    }
}

