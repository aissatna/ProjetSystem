#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include "../headers/fctsProjet.h"

/*---------- Fermeture des descripteurs non utilisés par le fils----------- */
void closeDescripteurFils(int i, int processNumber, int **pipeAnn, int **pipePereFils, int pipeFilsPere[2])
{

    close(pipeAnn[i][0]);
    if (i == 0)
    {
        close(pipeAnn[processNumber - 1][1]);
    }
    else
    {
        close(pipeAnn[i - 1][1]);
    }

    close(pipePereFils[i][1]);

    close(pipeFilsPere[0]);
}

/*----------Fermeture des descripteurs non utilisés par père----------- */

void closeDescripteurPere(int processNumber, int **pipePereFils, int pipeFilsPere[2])
{
    for (int i = 0; i < processNumber; i++)
    {
        close(pipePereFils[i][0]);
    }
    close(pipeFilsPere[1]);
}
/*---------- ---- Ecriture du père au fils ---------- */
void ecriturePereFils(int processNumber, int val, int **pipePereFils)
{
    for (int i = 0; i < processNumber; i++)
    {
        write(pipePereFils[i][1], &val, sizeof(int));
    }
    printf(" Je suis le père et j'envoie à mes fils le PID : %d\n", val);
}

/*----------  Ecriture du fils au père ----------*/
void ecritureFilsPere(int val, int pipeFilsPere[2])
{
    write(pipeFilsPere[1], &val, sizeof(int));
   
}

/*------------- fonction du choix du nombre de fils*----------*/
int saisirNbFils()
{
    int processNumber;
    do
    {
        printf("Nombre de fils a creer : ");
        scanf("%d", &processNumber);
        if (processNumber > 4)
        {
            printf("Donner un nombre!!valeur max est 4\n");
        }
    } while (processNumber > 4);

    return processNumber;
}

/*------------- Création des pipes ----------*/
int **creationPipe(int processNumber)
{
    int i;
    int **pipeAnn = malloc(sizeof(*pipeAnn) * processNumber);
    for (int i = 0; i < processNumber; i++)
    {
        pipeAnn[i] = malloc(sizeof(**pipeAnn) * 2);
        if (pipe(pipeAnn[i]) == -1)
        {
            perror("pipe");
            exit(-1);
        }
    }
    return pipeAnn;
}
/*-------- Envoi de l'information entre les fils ---------- */
void envoiFilsFils(int val, int i, int **pipeAnn)
{
    write(pipeAnn[i][1], &val, sizeof(int));
}
/*-------- Reception de l'information entre les fils ---------- */
int receptionFilsFils(int i, int processNumber, int **pipeAnn)
{
    int val;
    if (i == 0)
    {
        read(pipeAnn[processNumber - 1][0], &val, sizeof(int));
    }
    else
    {
        read(pipeAnn[i - 1][0], &val, sizeof(int));
    }
    return val;
}

/* Fonction qui permet au fils de lire  ce qui est envoyé par le père */

 int lectureDuPere(int descr)
{
    int val;

    read(descr, &val, sizeof(int));
    return val;
}
/* Fonction qui permet au père de lire  ce qui est envoyé par le fils */
 int lectureDuFils(int descr)
{
    int val;

    read(descr, &val, sizeof(int));
    return val;
}