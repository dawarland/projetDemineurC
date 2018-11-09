all : prog

prog: main.o CaseTerrain.o Partie.o Terrain.o
	gcc -o prog main.o CaseTerrain.o Partie.o Terrain.o

main.o: main.c
	gcc -c main.c

CaseTerrain.o: CaseTerrain.c Demineur.h
	gcc -c CaseTerrain.c

Partie.o: Partie.c Demineur.h
	gcc -c Partie.c

Terrain.o: Terrain.c Demineur.h
	gcc -c Terrain.c

clean: 
	rm -rf *o prog
