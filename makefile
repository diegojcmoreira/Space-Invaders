all: jogo.o spaceship.o bunker.o missil.o alien.o zbuffer.o
	g++ main.c jogo.o bunker.o missil.o spaceship.o alien.o zbuffer.o -o teste -lallegro -lallegro_dialog -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_ttf
	rm jogo.o
	rm spaceship.o
	rm bunker.o
	rm missil.o
	rm alien.o
	rm zbuffer.o

jogo.o:
	g++ -c jogo.c
spaceship.o:
	g++ -c spaceship.c
bunker.o:
	g++ -c bunker.c
missil.o:
	g++ -c missil.c
alien.o:
	g++ -c alien.c
zbuffer.o:
	g++ -c zbuffer.c


