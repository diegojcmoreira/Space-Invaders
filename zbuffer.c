// ZBuffer
  // Autor: GZS

  #include <stdlib.h>
  #include <stdio.h>
  #include <allegro5/allegro.h>

 
  #include "zbuffer.h"


  void inicializa_zbuffer( ZBuffer* z, ALLEGRO_DISPLAY *display,
       int altura, int largura, Bunker bunker[N_BUNKERS], SPACESHIP* spaceship, Alien alien[COLUNAS_TROPA][LINHAS_TROPA] )
  {
    z->display = display;
    z->buffer = al_create_bitmap( largura, altura );
    z->JANELA  = al_load_bitmap("imagens/espaco_sideral.jpg");

    if( z->JANELA == NULL ) 
    {
      puts( "Erro ao carregar o arquivo imagens/fundo.jpg");
      exit(0);
    }
    
    z->bunker = bunker;
    z->spaceship = spaceship;         
    
    //z->alien = alien;
    // z->n_misseis = n_misseis;
    // z->missel = m; 
  }

  void finaliza_zbuffer( ZBuffer*z ) {
    al_destroy_bitmap( z->JANELA );
    al_destroy_bitmap( z->buffer );
    
    al_destroy_display( z->display ); 
  }

  void processa_zbuffer( ZBuffer* z ) {
    al_set_target_bitmap( z->buffer );
    al_draw_bitmap( z->JANELA, 0, 0, 0 );
  
    //for( int i = 0; i < N_BUNKERS; i++ )
      //desenha_bunker( &z->bunker[i] );
    
    desenha_spaceship( z->spaceship );
    //desenha_tropa(z->alien);

    al_set_target_backbuffer( z->display );
    al_draw_bitmap( z->buffer, 0, 0, 0 );
    al_flip_display(); 
  }