#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "spaceship.h"

#define LARGURA_SPACESHIP 97.5
#define ALTURA_SPACESHIP  106

#define DELTA_X (-LARGURA_SPACESHIP/2)
#define DELTA_Y (-ALTURA_SPACESHIP)


void inicializa_spaceship( SPACESHIP* spaceship, int x, int y ) 
{
  spaceship->posicao_x = x + DELTA_X;
  spaceship->posicao_y = y + DELTA_Y;
  spaceship->min_x = spaceship->posicao_x + DELTA_X;
  spaceship->max_x = spaceship->posicao_x - DELTA_X;
  spaceship->min_y = spaceship->posicao_x + DELTA_Y;
  spaceship->min_y = spaceship->posicao_y;
  
  spaceship->bitmap = al_load_bitmap("imagens/tanque2.png");

  if( spaceship->bitmap == NULL) 
  {
    puts( "Erro ao carregar o arquivo imagens/tank.png");
    exit(0);
  }
}

void finaliza_spaceship( SPACESHIP* spaceship ) 
{
  al_destroy_bitmap( spaceship->bitmap );
}

void desenha_spaceship( SPACESHIP* spaceship ) 
{
  //puts("ENTROU EM desenha_spaceship");
    
  al_draw_bitmap( spaceship->bitmap, 
      spaceship->posicao_x , 
      spaceship->posicao_y , 0 );
  
}

void move_spaceship( SPACESHIP* spaceship, int delta_x, int delta_y ) 
{
  puts("ENTROU EM move_spaceship");
  spaceship->posicao_x += delta_x;
  spaceship->posicao_y += delta_y;  
  spaceship->min_x = spaceship->posicao_x + DELTA_X;
  spaceship->max_x = spaceship->posicao_x - DELTA_X;
  spaceship->min_y = spaceship->posicao_x + DELTA_Y;
  spaceship->min_y = spaceship->posicao_y;
}