// Jogo
// Autor: GZS
#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "jogo.h"

void inicializa_jogo( Jogo* jogo, int largura, int altura ) {
   if(!al_init()) {
      fprintf(stderr, "Falha ao inicializar o Allegro!\n");
      exit(-1);
   }
   
   if (!al_init_primitives_addon()) {
     fprintf(stderr, "Falha ao inicializar add-on de primitivas.\n");
     exit(-1);
   }

   if (!al_install_keyboard())
   {
     fprintf(stderr, "Falha ao inicializar o teclado.\n");
     exit(-1);
   }

   al_init_font_addon();
   if (!al_init_ttf_addon())
   {
    fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
    exit(-1);
   }
  
   if (!al_init_image_addon()) {
     fprintf(stderr, "Falha ao inicializar add-on de imagens.\n");
     exit(-1);
   }
   
   jogo->display = al_create_display( largura, altura );
   if(!jogo->display) {
      fprintf(stderr, "Falha ao criar o display!\n");
      exit(-1);
   }
   
   jogo->JANELA = al_load_bitmap("espaco_sideral.jpg");
   if (!jogo->JANELA)
    {
       fprintf(stderr, "Falha ao carregar o arquivo de imagem.\n");
       exit(-1);
    }

   jogo->altura = altura;
   jogo->largura = largura;

   al_draw_bitmap(jogo->JANELA, 0, 0, 0);
      
   for( int i = 0, x = (jogo->largura / 4 - TAMANHO_BUNKER) / 2; i < 4; i++, x += jogo->largura / 4 ) 
   {
     inicializa_bunker( &jogo->bunker[i], x, 360 );
   } 
   
   inicializa_tanque( &jogo->tanque, jogo->largura/2, 475 );
}

void inicio(Jogo* jogo) 
{
   int tecla = 0;
   desenha_jogo( jogo );

   ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
   fila_eventos = al_create_event_queue();
   if (!fila_eventos)
    {
       fprintf(stderr, "Falha ao criar fila de eventos.\n");
       exit(-1);
    }

    al_register_event_source(fila_eventos, al_get_display_event_source(jogo->display));
    
    while (1)
    {
        ALLEGRO_EVENT evento;
        ALLEGRO_TIMEOUT timeout;
        al_init_timeout(&timeout, 0.00000001);
        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
        al_register_event_source(fila_eventos, al_get_display_event_source(jogo->display));
 
 
        int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(evento.keyboard.keycode)
                {
                
                  case ALLEGRO_KEY_LEFT:
                    tecla = 1;
                    break;
                  
                  case ALLEGRO_KEY_RIGHT:
                    tecla = 2;
                    break;

                  case ALLEGRO_KEY_ESCAPE:
                    tecla = -1;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                 {
                    finaliza_jogo(jogo);
                    exit(0);
                 }

       if (tecla)
        { 
            switch (tecla)
            {
              case 1:
                move_tanque_jogo( jogo, ESQUERDA );
                break;

              case 2:
                move_tanque_jogo( jogo, DIREITA );
                break;

              case -1:
                finaliza_jogo(jogo);
                exit(0);

            }
 
            tecla = 0;
        }
    }

     al_destroy_event_queue(fila_eventos);
}

void finaliza_jogo( Jogo* jogo ) 
{
  for( int i = 0; i < 4; i++ )
    finaliza_bunker( &jogo->bunker[i] );

  al_destroy_bitmap(jogo->JANELA);
  al_destroy_display( jogo->display ); 
}

void desenha_jogo( Jogo* jogo ) 
{
   for( int i = 0; i < 4; i++ )
     desenha_bunker( &jogo->bunker[i] );
   
   desenha_tanque( &jogo->tanque, ESQUERDA );
   
   al_flip_display();  
}

void move_tanque_jogo( Jogo* jogo, DIRECAO direcao ) 
{
  switch( direcao ) 
  {
    case ESQUERDA :
      if( jogo->tanque.min_x > 0 ) 
      {
        move_tanque( &jogo->tanque, -5, 0 );
        al_draw_bitmap(jogo->JANELA, 0, 0, 0);
        desenha_jogo( jogo );
      }  
      break;

    case DIREITA :
      if( jogo->tanque.max_x < 639 ) 
      {
        move_tanque( &jogo->tanque, 5, 0 );
        al_draw_bitmap(jogo->JANELA, 0, 0, 0);
        desenha_jogo( jogo );
      }
      break;
  }
  
  al_flip_display();  
}