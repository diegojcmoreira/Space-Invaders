#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

#include "jogo.h"

int o = 0;

void inicializa_jogo( Jogo* jogo, int largura, int altura ) 
{https://snes1990.files.wordpress.com/2013/12/super-mario-bros-1985.png?w=300&h=290

  jogo->tempo = 0;
  jogo->altura = altura;
  jogo->largura = largura;
  jogo->N_DESTROYERS = 5;

  jogo->N_MISSEIS = 0;
  jogo->esquerda = true;
  
  inicializar_allegro();

  inicializar_fundo(jogo);

  inicializa_primitivas_allegro();

  inicializar_teclado_allegro();

  inicializar_fontes_allegro();

  inicializar_imagem_allegro();

  //inicializar_display(jogo);

  inicializar_fundo_allegro(jogo);
   //inicializa_buffer( &jogo->buffer, jogo->display, jogo->altura, jogo->largura, 
     //                  jogo->bunker, &jogo->spaceship );

      
   for( int i = 0, x = (jogo->largura / 4 - TAMANHO_BUNKER) / 2; i < 4; i++, x += jogo->largura / 4 ) 
   {
     inicializa_bunker( &jogo->bunker[i], x, 300 );
   } 
   
   inicializa_spaceship( &jogo->spaceship, jogo->largura/2, 475 );
   
   inicializa_eventos(jogo);

   inicializa_tropa(jogo->alien, 100, 10);

   
}

void inicio(Jogo* jogo) 
{
  bool saida = false;
  bool tecla[N_TECLAS] = {false, false};
  jogo->pause = false;
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

              case ALLEGRO_KEY_ESCAPE:
                jogo->pause = true;
                break;

              case ALLEGRO_KEY_S:
                inicializa_missil(&jogo->missil[jogo->N_MISSEIS], jogo->spaceship.posicao_x, jogo->spaceship.posicao_y, CIMA);
                //jogo->missil[jogo->N_MISSEIS].sentido = CIMA;
                jogo->N_MISSEIS++;
                


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

                case ALLEGRO_KEY_ESCAPE:
                  jogo->pause = false;
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
       
  }
}

void finaliza_jogo( Jogo* jogo ) 
{
  al_destroy_event_queue(jogo->fila_eventos);
   
  finaliza_spaceship( &jogo->spaceship );
  

  for( int i = 0; i < 4; i++ )
    finaliza_bunker( &jogo->bunker[i] );
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
  
}

void desenha_jogo( Jogo* jogo ) 
{
  al_draw_bitmap(jogo->JANELA, 0, 0, 0); 
  for( int i = 0; i < N_BUNKERS; i++ ) {
      desenha_bunker( &jogo->bunker[i] );
      colisao_missil_spaceship(jogo, &jogo->bunker[i]);}


  desenha_spaceship(&jogo->spaceship);
  //move_aliens (&jogo->alien[3][2], ESQUERDA);
  desenha_tropa(jogo->alien);
  //move_comboio (jogo->alien, ESQUERDA);
  //automatizacao_alien(jogo->alien);

  for (int i = 0; i < jogo->N_MISSEIS; i++) {
        desenha_missil(&jogo->missil[i]);
        move_missil(&jogo->missil[i], jogo->missil[i].sentido);
        
        if (jogo->missil[i].posicao_y < 0 - jogo->missil[i].altura) {
          //if(colisao(jogo->missil[i], alien)) 
            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;
          
        }
        else 
          if (jogo->missil[i].posicao_y > 700 - jogo->missil[i].altura) {
          //if(colisao(jogo->missil[i], alien)) 
            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;
          
        }

        /*if (colisao_missil_spaceship (&jogo->missil[i], &jogo->spaceship))
        {
            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;

        }*/
        /*for(int k = 0; k < COLUNAS_TROPA; k++ )
          for(int l = 0; l < LINHAS_TROPA; l++ )
            if (!(jogo->missil[i].posicao_y > jogo->alien[k][l].max_y  
                  || jogo->missil[i].posicao_x > jogo->alien[k][l].max_x
                  || jogo->missil[i].posicao_y + jogo->missil[i].altura < jogo->alien[k][l].posicao_y
                  || jogo->missil[i].posicao_x + jogo->missil[i].largura < jogo->alien[k][l].posicao_x) && jogo->alien[k][l].sentido && jogo->missil[i].sentido == CIMA)
            {    
                printf("%d\n", o++);
            }*/
          colisao(jogo, 1);
          colisao(jogo, 2);
       
            
    }     
        
  
  if(jogo->tempo == 50)
  {
  
      
      atira_comboio(jogo->alien, &jogo->missil[jogo->N_MISSEIS]);
      jogo->N_MISSEIS++;
      jogo->tempo = 0;
  }
      
      
    
    
    //printf("%d\n", jogo->N_MISSEIS );
  
  jogo->tempo++;

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

void colisao (Jogo* jogo, int teste)
{
  switch(teste) {

    case 1:
        for (int i = 0; i < jogo->N_MISSEIS; i++) 
          for (int k = 0; k < COLUNAS_TROPA; k++) 
            for (int l = 0; l < LINHAS_TROPA; l++) 
              if ((!(jogo->missil[i].posicao_x > jogo->alien[k][l].max_x
                    || jogo->missil[i].posicao_y > jogo->alien[k][l].max_y
                    || jogo->missil[i].posicao_y + jogo->missil[i].altura < jogo->alien[k][l].min_y
                    || jogo->missil[i].posicao_x + jogo->missil[i].largura < jogo->alien[k][l].min_x))
                    && jogo->alien[k][l].vivo 
                    && jogo->missil[i].sentido == CIMA) 
              {
                copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
                desenha_missil(&jogo->missil[i]);
                finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
                jogo->N_MISSEIS--;
                jogo->alien[k][l].vivo = false;
                return;
              }
            
          
       
        //break;

    case 2:
        for (int i = 0; i < jogo->N_MISSEIS; i++) 
          if (!(jogo->missil[i].posicao_y > jogo->spaceship.posicao_y + ALTURA_SPACESHIP 
              || jogo->missil[i].posicao_x > jogo->spaceship.posicao_x + LARGURA_SPACESHIP
              || jogo->missil[i].posicao_y + jogo->missil[i].altura < jogo->spaceship.posicao_y
              || jogo->missil[i].posicao_x + jogo->missil[i].largura < jogo->spaceship.posicao_x) 
              && jogo->missil[i].sentido == BAIXO)
          {
            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;
            return ;

          }
           
            
  }

  //switch(teste)
  //{
    
    /*case 1:
      for(int i = 0; i < jogo->N_MISSEIS; i++)
        if (!(missil->posicao_y > alien->max_y  
              || missil->posicao_x > alien->max_x
              || missil->posicao_y + missil->altura < alien->posicao_y
              || missil->posicao_x + missil->largura < alien->posicao_x) && alien->sentido)
        {    
            return true;
            break;
        }
      break;    
  }*/
}

void colisao_missil_spaceship (Jogo* jogo, Bunker* bunker) {

for (int i = 0; i < jogo->N_MISSEIS; i++) 
  for (int k = 0; k < PEDACOS_ALTURA; k++) 
    for (int l = 0; l < PEDACOS_LARGURA; l++)
      if ((!(jogo->missil[i].posicao_x > bunker->posicao_x + (bunker->largura/ PEDACOS_LARGURA)*l
        || jogo->missil[i].posicao_y > bunker->posicao_y + (bunker->altura/ PEDACOS_ALTURA)*k
        || jogo->missil[i].posicao_x + jogo->missil[i].largura < bunker->posicao_x +(bunker->largura/PEDACOS_LARGURA)*l 
        || jogo->missil[i].posicao_y + jogo->missil[i].altura < bunker->posicao_y + (bunker->altura/ PEDACOS_ALTURA)*k))) 
      {
          if (bunker->pedaco[l][k] != DESTRUIDO)
          {

            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;
            if (bunker->pedaco[l][k] == INTEIRO)
              bunker->pedaco[l][k] = AVARIADO;
            else if (bunker->pedaco[l][k] == AVARIADO)

            return ;
          }
    
      }
}
  
void menu(Jogo* jogo)
{
  while(!jogo->pause)
  {
    al_clear_to_color(al_map_rgba(0,0,0,100));
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

void inicializar_allegro()
{
    if(!al_init()) 
    {
      fprintf(stderr, "Falha ao inicializar o Allegro!\n");
      exit(-1);
    }
}

void inicializa_primitivas_allegro()
{
    if (!al_init_primitives_addon()) 
    {
      fprintf(stderr, "Falha ao inicializar add-on de primitivas.\n");
      exit(-1);
    }
}
  
void inicializar_teclado_allegro()
{
  if (!al_install_keyboard())
    {
      fprintf(stderr, "Falha ao inicializar o teclado.\n");
      exit(-1);
    }
}

void inicializar_fontes_allegro()
{
    al_init_font_addon();
    if (!al_init_ttf_addon())
    {
      fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
      exit(-1);
    }
}

void inicializar_imagem_allegro()
{
    if (!al_init_image_addon()) 
    {
      fprintf(stderr, "Falha ao inicializar add-on de imagens.\n");
      exit(-1);
    }
}

void inicializar_display(Jogo* jogo)
{
    jogo->display = al_create_display( jogo->largura, jogo->altura );
    if(!jogo->display) 
    {
      fprintf(stderr, "Falha ao criar o display!\n");
      exit(-1);
    }
}

void inicializar_fundo_allegro(Jogo* jogo)
{
    jogo->JANELA = al_load_bitmap("imagens/espaco_sideral.jpg");
    if (!jogo->JANELA)
    {
       fprintf(stderr, "Falha ao carregar o arquivo de imagem.\n");
       exit(-1);
    } 
}

void inicializar_tela_inicial(Jogo* jogo)
{
    jogo->TELA_INICIAL = al_load_bitmap("imagens/fundo2.png");
    if (!jogo->TELA_INICIAL)
    {
       fprintf(stderr, "Falha ao carregar o arquivo de imagem.\n");
       exit(-1);
    } 
}


void inicializar_todo_allegro() {

  inicializar_allegro();

  inicializa_primitivas_allegro();

  inicializar_teclado_allegro();

  inicializar_fontes_allegro();

  inicializar_imagem_allegro();

  
}

void inicializar_fundo(Jogo* jogo) {


  inicializar_display(jogo);

  inicializar_fundo_allegro(jogo);

  inicializar_tela_inicial(jogo);

}

void tela_inicial (Jogo* jogo)
{

   al_draw_bitmap(jogo->TELA_INICIAL, 0, 0, 0);

    al_flip_display();

    al_rest(10);
}