#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

#include "jogo.h"

#define FPS 60
#define N_TECLAS 3
#define LIMITE_DIREITO 630
#define LIMITE_ESQUERDO -20



void inicializa_jogo( Jogo* jogo, int largura, int altura ) 
{

  jogo->altura = altura;
  jogo->largura = largura;
  jogo->N_DESTROYERS = 5;

  jogo->N_MISSEIS = -1;
  jogo->esquerda = true;

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
   
   jogo->JANELA = al_load_bitmap("imagens/espaco_sideral.jpg");
   if (!jogo->JANELA)
    {
       fprintf(stderr, "Falha ao carregar o arquivo de imagem.\n");
       exit(-1);
    } 

   //inicializa_buffer( &jogo->buffer, jogo->display, jogo->altura, jogo->largura, 
     //                  jogo->bunker, &jogo->spaceship );

      
   for( int i = 0, x = (jogo->largura / 4 - TAMANHO_BUNKER) / 2; i < 4; i++, x += jogo->largura / 4 ) 
   {
     inicializa_bunker( &jogo->bunker[i], x, 360 );
   } 
   
   inicializa_spaceship( &jogo->spaceship, jogo->largura/2, 475 );
   
   inicializa_eventos(jogo);

   inicializa_tropa(jogo->alien, 100, 10);

   
}

void inicio(Jogo* jogo) 
{
  int atira = 0;
  bool saida = false;
  bool redraw = true;
  bool tecla[N_TECLAS] = {false, false};
  desenha_jogo(jogo);

  while( !saida ) 
  {
      desenha_jogo(jogo);
      if( !al_is_event_queue_empty(jogo->fila_eventos) ) 
      {
          ALLEGRO_EVENT evento;
          al_wait_for_event( jogo->fila_eventos, &evento );

          if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
             {
                saida = true;
                break;
             }
  
          if( evento.type == ALLEGRO_EVENT_KEY_DOWN )
            switch( evento.keyboard.keycode ) 
            {
              case ALLEGRO_KEY_LEFT: 
                tecla[TECLA_ESQUERDA] = true; 
                break;

              case ALLEGRO_KEY_RIGHT:
                tecla[TECLA_DIREITA] = true;
                break;

              case ALLEGRO_KEY_S:
                jogo->N_MISSEIS++;
                jogo->missil[jogo->N_MISSEIS].sentido = CIMA;
                inicializa_missil(&jogo->missil[jogo->N_MISSEIS], jogo->spaceship.posicao_x, jogo->spaceship.posicao_y, jogo->missil[jogo->N_MISSEIS].sentido);

                break;
            }
          
          if( evento.type == ALLEGRO_EVENT_KEY_UP ) 
            switch( evento.keyboard.keycode ) 
            {
                case ALLEGRO_KEY_LEFT: 
                  tecla[TECLA_ESQUERDA] = false;
                  break;
             
                case ALLEGRO_KEY_RIGHT:
                  tecla[TECLA_DIREITA] = false;
                  break;
                
                case ALLEGRO_KEY_Q: 
                  saida = true;
                  break;
            }
      }
      
        if( tecla[TECLA_DIREITA] )
          move_spaceship_jogo( jogo, DIREITA );
        if( tecla[TECLA_ESQUERDA] )   
          move_spaceship_jogo( jogo, ESQUERDA );
        if ( atira == 1)  
          //atirar(jogo, CIMA);         
          

        atira = 0;


  
  }
}

void finaliza_jogo( Jogo* jogo ) 
{
  al_destroy_event_queue(jogo->fila_eventos);
   
  finaliza_spaceship( &jogo->spaceship );
  

  //for( int i = 0; i < 4; i++ )
    //finaliza_bunker( &jogo->bunker[i] );
  al_destroy_bitmap(jogo->JANELA);
  al_destroy_display(jogo->display);
}

void move_spaceship_jogo( Jogo* jogo, DIRECAO direcao ) 
{
  switch( direcao ) 
  {
    case ESQUERDA :
      if( jogo->spaceship.min_x > LIMITE_ESQUERDO ) 
      {
        move_spaceship( &jogo->spaceship, -10, 0 );
      }  
      break;

    case DIREITA :
      if( jogo->spaceship.max_x < LIMITE_DIREITO ) 
      {
        move_spaceship( &jogo->spaceship, 10, 0 );

      }
      break;
  }
  
  //al_flip_display();  
}

void desenha_jogo( Jogo* jogo ) 
{

  al_draw_bitmap(jogo->JANELA, 0, 0, 0); 
  //for( int i = 0; i < N_BUNKERS; i++ )
    //  desenha_bunker( &jogo->bunker[i] );

  desenha_spaceship(&jogo->spaceship);
  desenha_tropa(jogo->alien);
  automatizacao_alien(jogo->alien);

  if (jogo->missil[jogo->N_MISSEIS].sentido == CIMA)
  {
    if ( jogo->N_MISSEIS > -1 )
    {
      if(jogo->missil[jogo->N_MISSEIS].posicao_y > 10)
      {
      //printf("a posicao_y na no inicio é :%d\n", jogo->missil[jogo->N_MISSEIS].posicao_y );

      move_missil(&jogo->missil[jogo->N_MISSEIS], CIMA);
      desenha_missil(&jogo->missil[jogo->N_MISSEIS]);
      }
      else
      {
        finaliza_missil(&jogo->missil[jogo->N_MISSEIS]);
        //printf("PRIMEIRO N_MISSEIS:%d\n",jogo->N_MISSEIS );
        jogo->N_MISSEIS--;
        //printf("SEGUNDO N_MISSEIS:%d\n",jogo->N_MISSEIS );

      }
    }
  }
  al_flip_display();
}

void inicializa_eventos (Jogo* jogo) 
{
  jogo->fila_eventos = al_create_event_queue();
    if (!jogo->fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        exit(-1);
    }

  al_register_event_source(jogo->fila_eventos, al_get_keyboard_event_source());
  al_register_event_source(jogo->fila_eventos, al_get_display_event_source(jogo->display));
}

void inicializa_timer_jogo (Jogo* jogo) 
{
  jogo->timer = al_create_timer(1.0/FPS);

  if(!jogo->timer)
  {
    fprintf(stderr, "Falha em executar timer!\n");
    exit(-1);
  }
}
/*
void atirar(Jogo* jogo, SENTIDO sentido)
{ 
  jogo->N_MISSEIS++;
  puts("FINALMENTE");

  if (jogo->N_MISSEIS < 5) 
  {
    puts("ENTROU NO IF");
    if (sentido == CIMA)
    {
      while (jogo->missil[jogo->N_MISSEIS].posicao_y > 10 )
      {
        puts("entrou no loop");
        desenha_jogo( jogo );
        
      }
    }

    if (sentido == BAIXO)
      while (jogo->missil[jogo->N_MISSEIS].posicao_y > jogo->altura)
      {
        move_missil(&jogo->missil[jogo->N_MISSEIS], BAIXO);
        desenha_jogo( jogo );

      }
  finaliza_missil(&jogo->missil[jogo->N_MISSEIS]);
  jogo->N_MISSEIS--;

  }
}*/
  
