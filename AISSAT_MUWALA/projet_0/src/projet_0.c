#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int processNumber;

    printf("Nombre de fils a creer: ");
    scanf("%d", &processNumber);
	for(int i = 0; i < processNumber; i++){
		switch (fork()){
			case -1 : // ERREUR
				fprintf(stderr, "Erreur de fork\n");
				exit(-1);
			case 0 : // Creation des fils
				printf("je suis %d, mon pid %d, mon pere Pid %d\n", i, getpid(), getppid());
				exit(-1);
	/****************************************************************************************/
			default :
			/* comportement du pere */
				while (wait(NULL)!=-1);
				printf("Done\n");
		}
	}	
    return 0;
}
