#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include "../headers/fctsProjetFinal.h"
/*---------- Fermeture des descripteurs non utilisés par le fils----------- */

void closeDescripteurFilsFinal(int i, int processNumber, int **pipeAnn, int **pipePereFils, int pipeFilsPere[2])
{

    close(pipeAnn[i][1]);
    if (i == 0)
    {
        close(pipeAnn[processNumber - 1][0]);
    }
    else
    {
        close(pipeAnn[i - 1][0]);
    }

    close(pipePereFils[i][1]);

    close(pipeFilsPere[1]);
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

/*----------Mise a jour des position des chevaux ----------- */
int majJeuPrincipal(int i, int de, int processNumber, int ***position)
{
    int val = position[i][i][0] + de;

    if (val >= 56)
    {
        position[i][i][0] = 56;
        return 1;
    }
    else
    {
        for (int j = 0; j < processNumber; j++)
        {
            if (position[i][j][0] == val)
            {
                position[i][j][0] = 0;
            }
        }
        position[i][i][0] = val;

        return 0;
    }
}

/*---------- ---- Ecriture du père au fils ---------- */
void ecriturePereFils(int processNumber, int val, int **pipePereFils)
{
    for (int i = 0; i < processNumber; i++)
    {
        write(pipePereFils[i][1], &val, sizeof(int));
    }
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
            printf("donner un nombre!!valeur max est 4\n");
        }
    } while (processNumber > 4);

    return processNumber;
}
/*------------- fonction Initialisation de jeu *----------*/
int ***initJeu(int processNumber)
{
    int c = 1, i, j, k;
    int ***A;
    A = (int ***)malloc(sizeof(int **) * processNumber);
    for (i = 0; i < processNumber; i++)
    {
        A[i] = (int **)malloc(sizeof(int *) * processNumber);
        for (j = 0; j < processNumber; j++)
        {
            A[i][j] = (int *)malloc(sizeof(int) * 1);
        }
    }
    for (i = 0; i < processNumber; i++)
    {
        for (j = 0; j < processNumber; j++)
        {
            for (k = 0; k < c; k++)
            {
                A[i][j][k] = 0;
            }
        }
    }

    return A;
}
/*------------- Création des pipes ----------*/
int **creationPipe(int processNumber)
{
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
/*******Fonction qui permet a chaque joeur de jouer  */
int jouer(int i, int processNumber, int numPlayer, int **pipeAnn, int **pipePereFils, int ***position)
{
    int de, controle;
    int sortie;

    if (numPlayer == getpid())
    {
        de = 1 + rand() % 6;
        int maj = majJeuPrincipal(i, de, processNumber, position);
        printf("\n                                            ");
        printf("\n joueur %d |valeur dé = %d ", getpid(), de);
        printf("\n********************************************\n");
        if (maj == 1)
            de = 0;
        envoiFilsFils(i, i, pipeAnn);
        envoiFilsFils(de, i, pipeAnn);
        int r = receptionFilsFils(i, processNumber, pipeAnn);
        int retour = receptionFilsFils(i, processNumber, pipeAnn);

        if (retour == 0)
        {
            controle = 1;
            printf("\x1b[44m GAGANT : %d\n\x1b[49m", getpid());
        }
        else if (retour == 6)
        {
            controle = 2;
        }
        else
        {
            controle = 0;
        }
    }
    else
    {
        int num = receptionFilsFils(i, processNumber, pipeAnn);
        int jeu = receptionFilsFils(i, processNumber, pipeAnn);

        if (jeu == 0)
        {

            printf("\x1b[44m PERDANT : %d\n\x1b[49m", getpid());
        }
        else
        {
            int val = position[i][num][0] + jeu;
            position[i][num][0] = val;
        }
        envoiFilsFils(num, i, pipeAnn);
        envoiFilsFils(jeu, i, pipeAnn);
    }

    return controle;
}
void affichage()
{
    printf("\n............................................................\n");
    printf("\n...................                    .....................\n");
    printf("\n.................. LES PETITS CHEVAUX  .....................\n");
    printf("\n...................                    .....................\n");
    printf("\n............................................................\n");
    printf("\n\n");
}