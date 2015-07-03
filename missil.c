#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "missil.h"
#include "jogo.h"


void inicializa_missil( Missil* missil, int posicao_x, int y, SENTIDO sentido ) 
{
  missil->posicao_x = posicao_x;
  missil->posicao_y = y;
  missil->velocidade = VELOCIDADE_MISSIL_SPACESHIP;
  missil->bitmap = al_load_bitmap("imagens/missil.jpg");
  missil->sentido = sentido;

  if( missil->bitmap == NULL) 
  {
    puts( "Erro ao carregar o arquivo imagens/tank.png");
    exit(0);
  }

  missil->altura = al_get_bitmap_height(missil->bitmap);
  missil->largura = al_get_bitmap_width(missil->bitmap);
}

void inicializa_missil_inimigo( Missil* missil, int posicao_x, int posicao_y, SENTIDO sentido ) 
{
  inicializa_imagem_missil(missil);
  missil->posicao_x = posicao_x;
  missil->posicao_y = posicao_y;
  missil->velocidade = VELOCIDADE_MISSIL_INIMIGO;
  missil->sentido = sentido;

  
  missil->altura = al_get_bitmap_height(missil->bitmap);
  missil->largura = al_get_bitmap_width(missil->bitmap);
}

void inicializa_imagem_missil(Missil* missil)
{
    missil->bitmap = al_load_bitmap("imagens/missil.jpg");
    if( missil->bitmap == NULL) 
  {
    puts( "Erro ao carregar o arquivo imagens/tank.png");
    exit(0);
  }

}

void finaliza_missil( Missil* missil ) 
{
  al_destroy_bitmap( missil->bitmap );
  
}

void desenha_missil( Missil* missil ) 
{
    al_draw_scaled_bitmap(missil->bitmap,
   0, 0, al_get_bitmap_width(missil->bitmap), al_get_bitmap_height(missil->bitmap),
   missil->posicao_x, missil->posicao_y, DISPLAY_WIDTH/200, DISPLAY_HEIGHT/26 , 0 );
}

void move_missil( Missil* missil, SENTIDO sentido )
{

  if (sentido == CIMA ) 
    missil->posicao_y -= missil->velocidade;
  if (sentido == BAIXO)
    missil->posicao_y += missil->velocidade; 
}

void copiar_missil (Missil* destino, Missil* origem) 
{
  destino->sentido = origem->sentido;
  destino->posicao_x = origem->posicao_x;
  destino->posicao_y = origem->posicao_y;
}
