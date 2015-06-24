#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

struct ZBuffer
{
  ALLEGRO_BITMAP* JANELA;
  Bunker bunker[4];
  Tanque tanque;
	
};

void inicializar_Zbuffer(ZBuffer* buffer, Jogo* jogo)
{
	buffer->display = jogo->display;
	buffer->JANELA = jogo->JANELA
	for( int i = 0; i < 4; i++) 
      buffer->bunker = jogo->bunker;
  	ZBuffer->tanque = jogo->tanque;
}
void Z_order (Jogo* jogo)
{
	al_draw_bitmap(jogo->JANELA, 0, 0, 0);
	desenha_jogo( jogo );



}