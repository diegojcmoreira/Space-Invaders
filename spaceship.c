#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "spaceship.h"
#include "zbuffer.h"




void inicializa_spaceship( SPACESHIP* spaceship, int x, int y ) 
{
  inicializa_bitmap_spaceship(spaceship);
  spaceship->altura_spaceship = DISPLAY_HEIGHT/8;//al_get_bitmap_height(spaceship->bitmap);
  spaceship->largura_spaceship = DISPLAY_WIDTH/19;//al_get_bitmap_width(spaceship->bitmap);
  spaceship->posicao_x = x - spaceship->largura_spaceship;
  spaceship->posicao_y = y - spaceship->altura_spaceship;
  spaceship->min_x = spaceship->posicao_x + DELTA_X;
  spaceship->max_x = spaceship->posicao_x - DELTA_X;
  spaceship->min_y = spaceship->posicao_y + DELTA_Y;
  spaceship->min_y = spaceship->posicao_y;
  
  
}

void finaliza_spaceship( SPACESHIP* spaceship ) 
{
  al_destroy_bitmap( spaceship->bitmap );
}

void desenha_spaceship( SPACESHIP* spaceship ) 
{
  al_draw_scaled_bitmap(spaceship->bitmap,
   0, 0, al_get_bitmap_width(spaceship->bitmap), al_get_bitmap_height(spaceship->bitmap),
   spaceship->posicao_x, spaceship->posicao_y, DISPLAY_WIDTH/19, DISPLAY_HEIGHT/8 , 0 );
    
  //al_draw_bitmap( spaceship->bitmap, 
     // spaceship->posicao_x , 
   //   spaceship->posicao_y , 0 );
  
}

void inicializa_bitmap_spaceship(SPACESHIP* spaceship)
{
  spaceship->bitmap = al_load_bitmap("imagens/tanque.png");

  if( spaceship->bitmap == NULL) 
  {
    puts( "Erro ao carregar o arquivo imagens/tank.png");
    exit(0);
  }

}

void move_spaceship( SPACESHIP* spaceship, int delta_x, int delta_y ) 
{
  //puts("ENTROU EM move_spaceship");
  spaceship->posicao_x += delta_x;
  spaceship->posicao_y += delta_y;  
  spaceship->min_x = spaceship->posicao_x + DELTA_X;
  spaceship->max_x = spaceship->posicao_x - DELTA_X;
  spaceship->min_y = spaceship->posicao_x + DELTA_Y;
  //spaceship->min_y = spaceship->posicao_y;
}