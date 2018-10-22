all: fctsProjet.o projet_1.o
		echo "all"
		gcc -o ./bin/projet_1 ./fctsProjet.o ./projet_1.o

fctsProjet.o :
		echo "fctsProjet.o"
		gcc -c ./src/fctsProjet.c -I ./headers	

projet_1.o :
		echo "projet_1.o"
		gcc -c ./src/projet_1.c -I ./headers			
clean:
		echo "clean"
		rm -rf ./*.o