#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char buf[128];
	int processNumber;
    printf("Nombre de fils a creer: ");
    scanf("%d", &processNumber);	

/*------------- Création des pipes ----------*/
	int **tab2 = malloc(sizeof(*tab2) * processNumber); 
	for (int i = 0; i < processNumber; i++){
    	tab2[i] = malloc(sizeof(**tab2) * 2);
		pipe(tab2[i]);
	}
/*------------- Création des process ----------*/
	for(int i = 0; i < processNumber; i++){
		switch (fork()){
			case -1 : // ERREUR
				perror("\x1B[31m Erreur de fork\n");
				exit(-1);
			case 0 :
/*------------- Création du fils ----------*/
                printf("je suis dan le fils %d\n",i);
				printf("I'm %d, my pid is %d, my dad Pid is %d\n", i, getpid(), getppid());
				if( i == 0){ // SI ON EST LE 1ER
					printf("i == 0 \n ");
					sprintf(buf, "Message de test process envoye par %d \n\0", i);
					close(tab2[i][0]);
					write(tab2[i][1], buf, 128);

					// Read retour
                    printf("avant1\n");
                   
					close(tab2[processNumber-1][1]);
                       printf("avant2\n");
                    int tailleLu = read(tab2[processNumber-1][0], buf, 128);
                       printf("avant 3\n");
					printf("\x1B[34m je suis le fils %d et j'ai lu le message %s\n",i,buf);
                    printf("avant 4\n");
					if(tailleLu == -1){
						perror("\x1b[31m Buffer error\n");
					}
					//printf("\x1b[33m je suis le fils %d STDERR BUFF taille lu = %d : ",i, tailleLu);
					//printf(buf);
					//close(tab2[i][1]);
                   // printf("apres read retour\n");
					
				}else{ // TOUS LES AUTRES FILS
					printf(" Entree Else fils \n");
					//close(tab2[i-1][1]);
					printf("Avant read \n ");
					//printf(buf);
					int tailleLu = read(tab2[i-1][0], buf, 128);
                   printf("\x1b[33m je suis le fils %d et j'ai lu le message %s",i,buf);
					printf("Après read \n ");
					close(tab2[i-1][0]);
					if(tailleLu == -1){
						perror("\x1B[31m Buffer error\n");
					}
					//printf("\x1B[35m je suis le fils %d STDERR BUFF taille lu = %d : ",i, tailleLu);
					
					//printf(buf);
					close(tab2[i][0]);
					int tailleEcrit = write(tab2[i][1], buf, 128);	
					//printf("\x1B[34m Process %d ecrit %d chars\n", i, tailleEcrit);
					if(tailleEcrit == -1){
						perror("\x1B[31m Buffer error\n");
					}		
				}

				exit(-1);
			/*default :
/*------------- Comportement du père ----------*/
				/*while (wait(NULL)!=-1);
				printf("\x1B[32m Done\n \x1B[37m");*/
		}
	}
	while (wait(NULL)!=-1);
	printf("\x1B[32m Done\n \x1B[37m");	
    return 0;
}