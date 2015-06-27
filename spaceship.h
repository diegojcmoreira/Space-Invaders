#ifndef SPACESHIP_H
#define SPACESHIP_H

enum DIRECAO { ESQUERDA, DIREITA, ALIEN_CIMA, ALIEN_BAIXO };

typedef struct nave
{
  int posicao_x, posicao_y;
  int min_x, max_x, min_y, max_y;
  ALLEGRO_BITMAP* bitmap;
} SPACESHIP;

void inicializa_spaceship( SPACESHIP* spaceship, int x, int y );

void finaliza_spaceship( SPACESHIP* spaceship );

void desenha_spaceship( SPACESHIP* spaceship ) ;

void move_spaceship( SPACESHIP* spaceship, int delta_x, int delta_y );

#endif
