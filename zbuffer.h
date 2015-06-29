// ZBuffer
// Autor: GZS

#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "spaceship.h"
#include "bunker.h"
#include "missil.h"
#include "alien.h"

#define MAX_MISSEIS 100
#define MAX_DESTROYERS 5
#define N_BUNKERS 4

struct ZBuffer 
{
  ALLEGRO_DISPLAY *display;
  ALLEGRO_BITMAP *buffer;

  ALLEGRO_BITMAP *JANELA;  		// 0 Z-order
  Bunker* bunker; 		// 1
  SPACESHIP* spaceship;
        		// 2
  Alien alien[COLUNAS_TROPA][LINHAS_TROPA];	// 3
  int n_misseis;
  Missil *missil[MAX_MISSEIS];	// 4 
} ;

void inicializa_zbuffer( ZBuffer* z, ALLEGRO_DISPLAY *display,
       int altura, int largura, Bunker bunker[N_BUNKERS], SPACESHIP* spaceship, Alien alien[COLUNAS_TROPA][LINHAS_TROPA] );

void finaliza_zbuffer( ZBuffer*z );

// Dá a cada objeto a sua chance de processamento, ou seja, "uma jogada".
void processa_zbuffer( ZBuffer* z );

#endif