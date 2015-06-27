all: jogo.o spaceship.o buffer.o bunker.o missil.o alien.o  
	g++ main.c jogo.o bunker.o buffer.o missil.o spaceship.o alien.o -o teste -lallegro -lallegro_dialog -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_ttf
	rm jogo.o
	rm spaceship.o
	rm bunker.o
	rm buffer.o
	rm missil.o
	rm alien.o

buffer.o:
	g++ -c buffer.c
jogo.o:
	g++ -c jogo.c
space_ship.o:
	g++ -c spaceship.c
bunker.o:
	g++ -c bunker.c
missil.o:
	g++ -c missil.c
alien.o:
	g++ -c alien.c


