#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include "../headers/fctsProjetFinal.h"
/* ---------------- MAIN -----------------*/
int main(int argc, char *argv[])
{

    int processNumber;
    int numFils[4]; //tableau pour le stockage des pid des fils

    /* saisir le nombre de joueurs*/
    processNumber = saisirNbFils();

    /*------------- Création des pipes ----------*/

    int **pipeAnn;
    int **pipePereFils;
    int pipeFilsPere[2];

    pipeAnn = creationPipe(processNumber);
    pipePereFils = creationPipe(processNumber);
    pipe(pipeFilsPere);
    int ***position;
    position = initJeu(processNumber);

    /* **************************Création des processus**************************/
    time_t t;
    srand((unsigned)time(&t));

    int controle = 0;
    bool Fa = false;

    affichage();
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

            while (!Fa)
            {
                int numPlayer = lectureDuPere(pipePereFils[i][0]);
                controle = jouer(i, processNumber, numPlayer, pipeAnn, pipePereFils, position);
                ecritureFilsPere(controle, pipeFilsPere);
                if (controle == 1)
                {

                    Fa = true;
                    closeDescripteurFilsFinal(i, processNumber, pipeAnn, pipePereFils, pipeFilsPere);
                }
            }
            for (int i = 0; i < processNumber; i++)
            {
                for (int j = 0; j < processNumber; j++)
                {
                    int k = 0;
                    // printf("position= %d\n", position[i][j][0]); // affichage des élément du tableau
                    printf("position[%i][%i][%i] = %d\n", i, j, k, position[i][j][k]); // affichage des élément du tableau
                }
            }
            exit(0);

        default:

            break;
        }
    }
    closeDescripteurPere(processNumber, pipePereFils, pipeFilsPere);

    int CP = 0;
    bool Fin = false;
    int compt = 0;
    while (!Fin)
    {
        ecriturePereFils(processNumber, numFils[compt], pipePereFils);
        if (compt == (processNumber - 1))
        {
            compt = 0;
        }
        else
        {
            compt += 1;
        }
        int CP = lectureDuFils(pipeFilsPere[0]);
        if (CP == 1)
            Fin = true;
    }
    for (int i = 0; i < processNumber; i++)
    {
        kill(numFils[i], SIGKILL);
    }

    while (wait(NULL) != -1)
        ;
    printf("\x1B[32m Done\n \x1B[37m");
    printf("\n............................................................\n");
    printf("\n...................                    .....................\n");
    printf("\n.................. FIN PARTIE   .....................\n");
    printf("\n...................                    .....................\n");
    printf("\n............................................................\n");
    printf("\n\n");
    return 0;
}
