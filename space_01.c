#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "jogo.h"
#include "bunker.h"
#include "tanque.h"

int main(int argc, char **argv){
   Jogo jogo;
   ALLEGRO_DISPLAY_MODE display_data;

   inicializa_jogo( &jogo, 640, 480);

   desenha_jogo( &jogo );

  	for( int i = 0; i < 400; i++ ) {
           move_tanque_jogo( &jogo, ESQUERDA );

    }
    
   al_rest(5);
   
   finaliza_jogo( &jogo );
   
   return 0;
}