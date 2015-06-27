  // ZBuffer
  // Autor: GZS

  #include <stdlib.h>
  #include <stdio.h>
  #include <allegro5/allegro.h>

  #include "jogo.h"
  #include "spaceship.h"
  #include "bunker.h"
  #include "buffer.h"


  void inicializa_buffer( BUFFER* buffer, ALLEGRO_DISPLAY *display,
        int altura, int largura, Bunker bunker[], SPACESHIP *spaceship ) 
{
    buffer->display = display;
    buffer->buffer = al_create_bitmap( largura, altura );
    buffer->JANELA  = al_load_bitmap("imagens/espaco_sideral.jpg");

    if( buffer->JANELA == NULL ) {
      puts( "Erro ao carregar o arquivo imagens/fundo.jpg");
      exit(0);
    }
    
    buffer->bunker = bunker;
    buffer->spaceship = spaceship;         
    
    // z->aliens = a;
    // z->n_misseis = n_misseis;
    // z->missel = m; 
  }

  void finaliza_buffer( BUFFER* buffer ) {
    al_destroy_bitmap( buffer->JANELA );
    al_destroy_bitmap( buffer->buffer );
    
    al_destroy_display( buffer->display ); 
  }


  void processa_buffer( BUFFER* buffer ) 
  {

    
    al_flip_display(); 
  }
