#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "jogo.h"
#include "bunker.h"
#include "spaceship.h"

int main(int argc, char **argv){
   Jogo jogo;
   ALLEGRO_DISPLAY_MODE display_data;

   inicializa_jogo( &jogo, 640, 480);
   
   inicio(&jogo);
   
   finaliza_jogo( &jogo );
   
   return 0;
}