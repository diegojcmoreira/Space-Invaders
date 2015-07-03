all: jogo.o spaceship.o bunker.o missil.o inimigo.o placar.o vidas.o death_star.o
	g++ -g main.c jogo.o bunker.o missil.o placar.o death_star.o vidas.o spaceship.o inimigo.o -o teste -lallegro -lallegro_dialog -lallegro_image -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_ttf
	rm jogo.o
	rm spaceship.o
	rm bunker.o
	rm missil.o
	rm inimigo.o
	rm placar.o
	rm vidas.o
	rm death_star.o

jogo.o:
	g++ -c jogo.c
spaceship.o:
	g++ -c spaceship.c
bunker.o:
	g++ -c bunker.c
missil.o:
	g++ -c missil.c
inimigo.o:
	g++ -c inimigo.c
placar.o:
	g++ -c placar.c
vidas.o:
	g++ -c vidas.c
death_star.o:
	g++ -c death_star.c


