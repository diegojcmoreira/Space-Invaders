#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "missil.h"
#include "jogo.h"
#include "zbuffer.h"


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
  //printf("largura do bitmap:%d\naltura do bitmap%d\n", missil->largura, missil->altura );

  //puts("SAIU DE inicializa_missil");
}

void inicializa_missil_inimigo( Missil* missil, int posicao_x, int y, SENTIDO sentido ) 
{
  missil->posicao_x = posicao_x;
  missil->posicao_y = y;
  missil->velocidade = VELOCIDADE_MISSIL_INIMIGO;
  missil->bitmap = al_load_bitmap("imagens/missil.jpg");
  missil->sentido = sentido;

  if( missil->bitmap == NULL) 
  {
    puts( "Erro ao carregar o arquivo imagens/tank.png");
    exit(0);
  }

  missil->altura = al_get_bitmap_height(missil->bitmap);
  missil->largura = al_get_bitmap_width(missil->bitmap);
  //printf("largura do bitmap:%d\naltura do bitmap%d\n", missil->largura, missil->altura );

  //puts("SAIU DE inicializa_missil");
}

void finaliza_missil( Missil* missil ) 
{
  al_destroy_bitmap( missil->bitmap );
}

void desenha_missil( Missil* missil ) 
{
   // puts("entrou em desenha_missil");
    //printf("posicao_x é :%d\nposição y é : %d\n", missil->posicao_x, missil->posicao_y );

    al_draw_bitmap( missil->bitmap, 
      missil->posicao_x , 
      missil->posicao_y , 0);
   // puts("PASSOU DE ONDE EU ACHAVA QUE ERA O Erro") ; 
}

void move_missil( Missil* missil, SENTIDO sentido )
{
  //puts("entrou em move_missil");

  if (sentido == CIMA ) 
    missil->posicao_y -= missil->velocidade;
  if (sentido == BAIXO)
    missil->posicao_y += missil->velocidade; 
  //printf("a posicao_y na função move_missil é :%d\n",missil->posicao_y );
}

void copiar_missil (Missil* destino, Missil* origem) 
{
  destino->sentido = origem->sentido;
  destino->posicao_x = origem->posicao_x;
  destino->posicao_y = origem->posicao_y;
}
