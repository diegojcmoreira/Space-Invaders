#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "define.h"



 struct SPACESHIP
{
  int posicao_x, posicao_y, min_x, max_x, min_y, max_y, altura_spaceship, largura_spaceship;
  ALLEGRO_BITMAP* bitmap;
 
};

void inicializa_spaceship( SPACESHIP* spaceship, int x, int y );

void finaliza_spaceship( SPACESHIP* spaceship );

void desenha_spaceship( SPACESHIP* spaceship ) ;

void move_spaceship( SPACESHIP* spaceship, int delta_x, int delta_y );

void inicializa_bitmap_spaceship(SPACESHIP* spaceship);


#endif
