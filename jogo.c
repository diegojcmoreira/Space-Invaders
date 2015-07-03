#include <stdlib.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>

#include "jogo.h"


void inicializa_jogo( Jogo* jogo, int largura, int altura ) 
{

  jogo->ativar_death_star = 0;
  jogo->altura = altura;
  jogo->largura = largura;
  jogo->misseis_ativos_spaceship = 0;

  jogo->N_MISSEIS = 0;
  //jogo->esquerda = true;

  
  inicializar_allegro();

  inicializar_fundo(jogo);

  inicializa_primitivas_allegro();

  inicializar_teclado_allegro();

  inicializar_fontes_allegro();

  inicializar_imagem_allegro();

  inicializar_fundo_allegro(jogo);

  inicializa_timer_jogo(jogo);

  inicializar_fontes_menu_pause (jogo);


  inicializa_spaceship( &jogo->spaceship, jogo->largura/2, DISPLAY_HEIGHT - 15 );

      
  for( int i = 0, x = (jogo->largura / N_BUNKERS - TAMANHO_BUNKER) / 2; i < N_BUNKERS; i++, x += jogo->largura / N_BUNKERS ) 
  {
    inicializa_bunker( &jogo->bunker[i], x, jogo->spaceship.posicao_y - 80 );
  } 
 
  inicializa_death_star (&jogo->death_star, 0  , POSICAO_Y_VIDA + 20); 

  inicializa_eventos(jogo);

  inicializa_placar(&jogo->placar);

  inicializa_tropa(jogo->inimigo, 200, jogo->death_star.posicao_y + 40);

  inicializa_vidas(&jogo->vidas);

   
}

void inicio(Jogo* jogo) 
{
  bool tecla[N_TECLAS] = {false, false};
  jogo->saida = false;
  desenha_jogo(jogo);

  while( !jogo->saida ) 
  {
      
      al_start_timer(jogo->timer);

      if( !al_is_event_queue_empty(jogo->fila_eventos) ) 
      {
          ALLEGRO_EVENT evento;
          al_wait_for_event( jogo->fila_eventos, &evento );

          if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
             {
                jogo->saida = true;
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
              if(jogo->misseis_ativos_spaceship < MAX_TIROS_SPACESHIP)
              {
                inicializa_missil(&jogo->missil[jogo->N_MISSEIS], 
                (jogo->spaceship.posicao_x + (jogo->spaceship.largura_spaceship/2)) - jogo->missil[jogo->N_MISSEIS].largura,
                 jogo->spaceship.posicao_y, CIMA);
                jogo->N_MISSEIS++;
                jogo->misseis_ativos_spaceship++;
              }
                break;
                
            }
          
          if( evento.type == ALLEGRO_EVENT_TIMER )
          {
               if(jogo->ativar_death_star == 15)
               {
                 jogo->death_star.movimento_death_star = true;
                 jogo->ativar_death_star = 0;

               }
               
               if (!jogo->death_star.movimento_death_star)
                  jogo->ativar_death_star ++;

              atira_comboio(jogo->inimigo, &jogo->missil[jogo->N_MISSEIS]);
              jogo->N_MISSEIS++;
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
                  jogo->saida = true;
                  break;

            }
      }
      
        if( tecla[TECLA_DIREITA] )
          move_spaceship_jogo( jogo, DIREITA );
        if( tecla[TECLA_ESQUERDA] )   
          move_spaceship_jogo( jogo, ESQUERDA );

        colisao(jogo, ALIEN);
        colisao(jogo, SPACESHIP_);
        colisao(jogo, BUNKER);
        colisao_death_star(jogo);
        invadiu_base(jogo);


        

        
        if(!inimigo_vivo(jogo->inimigo))
          winner (jogo);   
        
        desenha_jogo(jogo);
  }
}

void finaliza_jogo( Jogo* jogo ) 
{
  al_destroy_event_queue(jogo->fila_eventos);
  al_destroy_event_queue(jogo->apos_perder);
   
  finaliza_spaceship( &jogo->spaceship );
  finaliza_inimigo(jogo->inimigo);
  finaliza_death_star (&jogo->death_star);
  

  for( int i = 0; i < N_BUNKERS; i++ )
    finaliza_bunker( &jogo->bunker[i] );

  finaliza_placar(&jogo->placar);
  finaliza_vidas(&jogo->vidas);
  al_destroy_font(jogo->fonte);
  al_destroy_timer(jogo->timer);
  al_destroy_bitmap(jogo->JANELA);
  al_destroy_display(jogo->display);
}

void move_spaceship_jogo( Jogo* jogo, DIRECAO direcao ) 
{
  switch( direcao ) 
  {
    case ESQUERDA :

      if( jogo->spaceship.min_x > 0 - (jogo->spaceship.largura_spaceship/2)) 
      {
        move_spaceship( &jogo->spaceship, -10, 0 );
      }  
      break;

    case DIREITA :
      if( jogo->spaceship.max_x < DISPLAY_WIDTH - (jogo->spaceship.largura_spaceship/2) ) 
      {
        move_spaceship( &jogo->spaceship, 10, 0 );

      }
      break;
  }  
}

void desenha_jogo( Jogo* jogo ) 
{
  desenha_fundo(jogo);
  
  for( int i = 0; i < N_BUNKERS; i++ )
      desenha_bunker( &jogo->bunker[i] );

  if(jogo->death_star.movimento_death_star)
          automatiza_death_star(&jogo->death_star);

  desenha_spaceship(&jogo->spaceship);
  desenha_tropa(jogo->inimigo);
  automatizacao_inimigo(jogo->inimigo);
  teste_limites (jogo);

  desenha_vidas(&jogo->vidas);
  desenha_placar(&jogo-> placar);  
  

  al_flip_display();
}

void inicializa_eventos (Jogo* jogo) 
{
  jogo->fila_eventos = al_create_event_queue();
  jogo->apos_perder = al_create_event_queue();
    if (!(jogo->fila_eventos||jogo->apos_perder))
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        exit(-1);
    }

  al_register_event_source(jogo->fila_eventos, al_get_keyboard_event_source());
  al_register_event_source(jogo->fila_eventos, al_get_display_event_source(jogo->display));
  al_register_event_source(jogo->fila_eventos, al_get_timer_event_source(jogo->timer));
  al_register_event_source(jogo->apos_perder, al_get_keyboard_event_source());

}

void teste_limites (Jogo* jogo)
{
  for (int i = 0; i < jogo->N_MISSEIS; i++) {
        desenha_missil(&jogo->missil[i]);
        move_missil(&jogo->missil[i], jogo->missil[i].sentido);
        
        if (jogo->missil[i].posicao_y < 0 - jogo->missil[i].altura) {
            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;
            jogo->misseis_ativos_spaceship--;
          
        }
        else 
          if (jogo->missil[i].posicao_y > 700 - jogo->missil[i].altura) {
            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;
          
        }
          
  }
}

void inicializa_timer_jogo (Jogo* jogo) 
{
  jogo->timer = al_create_timer(INTERVALO_ALIEN_ATIRAR/FPS);

  if(!jogo->timer)
  {
    fprintf(stderr, "Falha em executar timer!\n");
    exit(-1);
  }
}

void colisao (Jogo* jogo, COLISAO colisao)
{
  switch(colisao) 
  {

    case ALIEN:
        for (int i = 0; i < jogo->N_MISSEIS; i++) 
          for (int k = 0; k < COLUNAS_TROPA; k++) 
            for (int l = 0; l < LINHAS_TROPA; l++) 
              if ((!(jogo->missil[i].posicao_x > (jogo->inimigo[k][l].max_x - 15)
                    || jogo->missil[i].posicao_y > jogo->inimigo[k][l].max_y
                    || jogo->missil[i].posicao_y + jogo->missil[i].altura < jogo->inimigo[k][l].posicao_y
                    || jogo->missil[i].posicao_x + jogo->missil[i].largura < jogo->inimigo[k][l].posicao_x))
                    && jogo->inimigo[k][l].vivo 
                    && jogo->missil[i].sentido == CIMA) 
              {
                  copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
                  desenha_missil(&jogo->missil[i]);
                  finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
                  jogo->N_MISSEIS--;
                  jogo->misseis_ativos_spaceship--;
                  jogo->inimigo[k][l].vivo = false;
                  jogo->placar.pontuacao += INIMIGOS_PONTOS;
                  return;

              }
            
    case SPACESHIP_:
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
              jogo->vidas.chances -= 1;
              perdendo_para_maquina(jogo);
            return ;
          }

    case BUNKER:
      for( int i = 0; i < N_BUNKERS; i++ )
        colisao_missil_bunker (jogo, &jogo->bunker[i]);
        break;

    case DEATH_STAR:
        for (int i = 0; i < jogo->N_MISSEIS; i++) 
          if (!(jogo->missil[i].posicao_y > jogo->death_star.posicao_y + jogo->death_star.altura
              || jogo->missil[i].posicao_x > jogo->death_star.posicao_x + jogo->death_star.posicao_y
              || jogo->missil[i].posicao_y + jogo->missil[i].altura < jogo->death_star.posicao_y
              || jogo->missil[i].posicao_x + jogo->missil[i].largura < jogo->death_star.posicao_x))
          {
            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;
            jogo->placar.pontuacao += DEATH_STAR_PONTOS;
            reinicializar_death_star (&jogo->death_star);
          }
          break;

  }

}

void perdendo_para_maquina(Jogo* jogo)
{
  if (jogo->vidas.chances > -1)
      perdeu_vida(jogo);


  else{
      al_draw_text(jogo->fonte , 
        al_map_rgb(255,255,255), 
        DISPLAY_WIDTH/2, 
        (DISPLAY_HEIGHT/2)-70, ALLEGRO_ALIGN_CENTER, "GAME OVER");
      
      al_flip_display();
      al_rest(3);
      jogo->saida = true;
  }
}

void colisao_missil_bunker (Jogo* jogo, Bunker* bunker) 
{
  for (int i = 0; i < jogo->N_MISSEIS; i++) 
    for (int k = 0; k < PEDACOS_ALTURA; k++) 
      for (int l = 0; l < PEDACOS_LARGURA; l++)
        if ((!(jogo->missil[i].posicao_x > bunker->posicao_x + (bunker->largura/ PEDACOS_LARGURA)*(l+1)
          || jogo->missil[i].posicao_y > bunker->posicao_y + (bunker->altura/ PEDACOS_ALTURA)*(k+1)
          || jogo->missil[i].posicao_x + jogo->missil[i].largura < bunker->posicao_x +(bunker->largura/PEDACOS_LARGURA)*l 
          || jogo->missil[i].posicao_y + jogo->missil[i].altura < bunker->posicao_y + (bunker->altura/ PEDACOS_ALTURA)*k))
          && bunker->pedaco[l][k] != DESTRUIDO) 
        {
              if(jogo->missil[i].sentido == CIMA)
                jogo->misseis_ativos_spaceship--;
              copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
              desenha_missil(&jogo->missil[i]);
              finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
              jogo->N_MISSEIS--;
              if (bunker->pedaco[l][k] == INTEIRO)
                bunker->pedaco[l][k] = AVARIADO;
              else if (bunker->pedaco[l][k] == AVARIADO)
                bunker->pedaco[l][k] = DESTRUIDO;

              return ;    
        }
}

void colisao_death_star(Jogo* jogo)
{

  for (int i = 0; i < jogo->N_MISSEIS; i++) 
          if (!(jogo->missil[i].posicao_y > jogo->death_star.posicao_y + jogo->death_star.altura
              || jogo->missil[i].posicao_x > jogo->death_star.posicao_x + jogo->death_star.posicao_y
              || jogo->missil[i].posicao_y + jogo->missil[i].altura < jogo->death_star.posicao_y
              || jogo->missil[i].posicao_x + jogo->missil[i].largura < jogo->death_star.posicao_x))
          {
            copiar_missil(&jogo->missil[i], &jogo->missil[jogo->N_MISSEIS-1]);
            desenha_missil(&jogo->missil[i]);
            finaliza_missil(&jogo->missil[jogo->N_MISSEIS-1]);
            jogo->N_MISSEIS--;
            jogo->misseis_ativos_spaceship--;
            jogo->placar.pontuacao += DEATH_STAR_PONTOS;
            reinicializar_death_star (&jogo->death_star);
          }
}

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
    jogo->JANELA = al_load_bitmap("imagens/fundo2.jpg");
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


void inicializar_todo_allegro() 
{

  inicializar_allegro();

  inicializa_primitivas_allegro();

  inicializar_teclado_allegro();

  inicializar_fontes_allegro();

  inicializar_imagem_allegro();

  
}

void inicializar_fundo(Jogo* jogo) 
{


  inicializar_display(jogo);

  inicializar_fundo_allegro(jogo);

  inicializar_tela_inicial(jogo);

}

void desenha_fundo(Jogo* jogo)
{
  
  al_draw_scaled_bitmap(jogo->JANELA,
   0, 0, al_get_bitmap_width(jogo->JANELA), al_get_bitmap_height(jogo->JANELA),
   0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0 );
    
}

void tela_inicial (Jogo* jogo)
{

   al_draw_bitmap(jogo->TELA_INICIAL, 0, 0, 0);

    al_flip_display();

    al_rest(5);
}

void perdeu_vida(Jogo* jogo)
{
  bool voltar = false;
  bool tecla[N_TECLAS] = {false, false};
  al_stop_timer(jogo->timer);

  while( !voltar ) 
  {
    fundo_pause(jogo);

    al_map_rgba(VERDE_CLARO, 200);

      if( !al_is_event_queue_empty(jogo->apos_perder) ) 
      {
          ALLEGRO_EVENT evento;
          al_wait_for_event( jogo->apos_perder, &evento );

  
          if( evento.type == ALLEGRO_EVENT_KEY_DOWN )
            switch( evento.keyboard.keycode ) 
            {
              case ALLEGRO_KEY_LEFT: 
                tecla[TECLA_ESQUERDA] = true; 
                break;

              case ALLEGRO_KEY_RIGHT:
                tecla[TECLA_DIREITA] = true;
                break;

              case ALLEGRO_KEY_ENTER:
                voltar = true;
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

                case ALLEGRO_KEY_ENTER:
                  voltar = false;
                  break;
              
            }
      
      }
      
        if( tecla[TECLA_DIREITA] )
          move_spaceship_jogo( jogo, DIREITA );
        if( tecla[TECLA_ESQUERDA] )   
          move_spaceship_jogo( jogo, ESQUERDA );
       
  }
}

void fundo_pause (Jogo* jogo)
{
  desenha_fundo(jogo);
  

  for( int i = 0; i < N_BUNKERS; i++ )
      desenha_bunker( &jogo->bunker[i] );

  desenha_spaceship(&jogo->spaceship);
  desenha_tropa(jogo->inimigo);

  desenha_vidas(&jogo->vidas);
  desenha_placar(&jogo-> placar);

  al_draw_textf(jogo->fonte , al_map_rgb(255,255,255), DISPLAY_WIDTH/2, (DISPLAY_HEIGHT/2) - 80, ALLEGRO_ALIGN_CENTER, "Lhe restam %d vidas", jogo->vidas.chances);
  al_draw_textf(jogo->fonte , al_map_rgb(255,255,255), DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, ALLEGRO_ALIGN_CENTER, "posicione a spaceship no local desejado");
  al_draw_textf(jogo->fonte , al_map_rgb(255,255,255), DISPLAY_WIDTH/2, (DISPLAY_HEIGHT/2) + 80, ALLEGRO_ALIGN_CENTER, "e tecle enter para retornar");


  al_flip_display();
}

void inicializar_fontes_menu_pause (Jogo* jogo)
{
   jogo->fonte = al_load_font("fontes/HARRYP.ttf", TAMANHO_FONTE_PAUSE, 0);
   if (!jogo->fonte)
    {
        fprintf(stderr, "Falha ao carregar fonte.\n");
        exit(-1);
    }
}

void winner (Jogo* jogo)
{
  ALLEGRO_BITMAP* img;
  ALLEGRO_FONT* fonte;
  fonte = al_load_font("fontes/HARRYP.ttf", 50, 0);
  img = al_load_bitmap("imagens/winner.jpg");
  //al_draw_bitmap(img,0,0,0);
  al_draw_scaled_bitmap(img,
   0, 0, al_get_bitmap_width(img), al_get_bitmap_height(img),
   0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT , 0 );

  al_draw_text(fonte, al_map_rgb(255,255,255), DISPLAY_WIDTH/2, DISPLAY_HEIGHT - 100, ALLEGRO_ALIGN_CENTER, "WINNER" );
  al_flip_display();
  al_rest(6);
  jogo->saida = true;

  al_destroy_font(fonte);
  al_destroy_bitmap(img);
}

void invadiu_base(Jogo* jogo)
{
  for (int i = 0; i < COLUNAS_TROPA ; i++)
    for (int j = 0; j < LINHAS_TROPA ; j++)
      if ((jogo->inimigo[i][j].vivo) && (jogo->inimigo[i][j].max_y > jogo->bunker[0].posicao_y) )
      {
        al_draw_text(jogo->fonte , 
            al_map_rgb(255,255,255), 
            DISPLAY_WIDTH/2, 
            (DISPLAY_HEIGHT/2)-70, ALLEGRO_ALIGN_CENTER, "GAME OVER");
          
            al_flip_display();
            al_rest(3);
            jogo->saida = true;
      }
}