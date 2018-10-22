all: fctsProjetFinal.o projetFinal.o
		echo "all"
		gcc -o ./bin/projetFinal ./fctsProjetFinal.o ./projetFinal.o

fctsProjetFinal.o :
		echo "fctsProjetFinal.o"
		gcc -c ./src/fctsProjetFinal.c -I ./headers	

projetFinal.o :
		echo "projetFinal.o"
		gcc -c ./src/projetFinal.c -I ./headers			
clean:
		echo "clean"
		rm -rf ./*.o