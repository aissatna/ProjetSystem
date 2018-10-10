#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int NbProcess;
    printf("Donnez le Nombre de fils: \n");
    scanf("%d", &NbProcess);
    for (int i = 0; i < NbProcess; i++)
    {
        switch (fork())
        {
        case -1:
            fprintf(stderr, "Erreur de fork\n");
            exit(-1);
        case 0:
      
            /* comportement du fils 1 */
            printf("Le fils numero %d, Mon Numero :%d, Mon père: %d\n", i, getpid(), getppid());
            exit(-1);
        default:

            /* comportement du père */
            while (wait(NULL) != -1) ;
        }
    }
    return 0;
}
