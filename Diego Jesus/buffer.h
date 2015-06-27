// ZBuffer
// Autor: GZS

#ifndef BUFFER_H
#define BUFFER_H

struct BUFFER {
  ALLEGRO_DISPLAY *display;
  ALLEGRO_BITMAP *buffer;

  ALLEGRO_BITMAP *JANELA;  		// 0 Z-order
  Bunker* bunker; 		// 1
  SPACESHIP* spaceship;         		// 2
  // Alien* aliens[N_LINHAS_ALIENS][N_COLUNAS_ALIENS]; 	// 3
  int N_MISSEIS;
  // Misseis *missel[N_MAX_MISSEIS];	// 4 
};
void inicializa_buffer( BUFFER* buffer, ALLEGRO_DISPLAY *display,
        int altura, int largura, Bunker bunker[], SPACESHIP *spaceship );

void finaliza_buffer( BUFFER* buffer );

void finaliza_buffer( BUFFER* buffer );
// Dá a cada objeto a sua chance de processamento, ou seja, "uma jogada".
void processa_buffer( BUFFER* buffer );

#endif