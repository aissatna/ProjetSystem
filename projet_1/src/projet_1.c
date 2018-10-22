
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "../headers/fctsProjet.h"

/*-------------main ------------------ */

int main(int argc, char *argv[])
{
    int processNumber;
    int numFils[4]; //tableau pour le stockage des pid des fils
    processNumber = saisirNbFils();

    /*------------- Création des pipes ----------*/
    int **pipeAnn;
    int **pipePereFils;
    int pipeFilsPere[2];
    pipeAnn = creationPipe(processNumber);
    pipePereFils = creationPipe(processNumber);
    pipe(pipeFilsPere);

    /* ----------------- Création des processus-----------------------*/
    for (int i = 0; i < processNumber; i++)
    {
        switch (numFils[i] = fork())
        {
        case -1:
            /**--------Cas erreur fork----------*/
            perror("\x1B[31m Erreur de fork\n");
            exit(-1);
        case 0: /**--------Cas comportement fils*/
            //traitement des descripteurs
            closeDescripteurFils(i, processNumber, pipeAnn, pipePereFils, pipeFilsPere);
            int val = lectureDuPere(pipePereFils[i][0]);
             printf("\x1B[32m je suis le fils %d, mon PID %d, j'ai recu de père %d \n",i, getpid(), val);
            if (val == getpid())
            {
                envoiFilsFils(100, i, pipeAnn);
                int retour = receptionFilsFils(i, processNumber, pipeAnn);
                printf("\x1B[32m Je suis le fils PID %d, et j'ai recu %d\n", getpid(), retour);
                ecritureFilsPere(retour, pipeFilsPere);
               
            }
            else
            {
                int jeu = receptionFilsFils(i, processNumber, pipeAnn);
                printf("\x1B[32m Je suis le fils PID %d, et j'ai recu %d\n", getpid(), jeu);
                envoiFilsFils(jeu, i, pipeAnn);
            }

            exit(0);
        default:
            break;
        }
    }
    // Affichage des PID des fils 
    printf("\x1B[37m je suis le père et les PID de mes fils sont:\t"); 
    for (int i = 0; i < processNumber; i++)
    {
        printf("%d\t", numFils[i]);
    }
     printf("\n");
    closeDescripteurPere(processNumber, pipePereFils, pipeFilsPere);
    ecriturePereFils(processNumber, numFils[0], pipePereFils);
    int val = lectureDuFils(pipeFilsPere[0]);
    printf("\x1B[34m je suis le père et j'ai recu du fils %d \n", val);
    
    while (wait(NULL) != -1) ;
    printf("\x1B[32m Done\n \x1B[37m");
    return 0;
}
