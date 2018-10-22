#ifndef FCTSPROJETFINAL_H
#define FCTSPROJETFINAL_H
void closeDescripteurFilsFinal(int i, int processNumber,int **pipeAnn,int **pipePereFils,int pipeFilsPere[2]);
void closeDescripteurPere(int processNumber,int **pipePereFils,int pipeFilsPere[2]);
 int majJeuPrincipal(int i,int de,int processNumber, int *** position );
void ecriturePereFils(int processNumber,int val,int **pipePereFils);
void ecritureFilsPere(int val, int pipeFilsPere[2]);
int saisirNbFils();
int*** initJeu(int processNumber);
int **creationPipe(int processNumber);
void envoiFilsFils(int val,int i,int ** pipeAnn);
int lectureDuPere (int descr);
int lectureDuFils(int descr);
int jouer(int i,int processNumber,int numPlayer, int **pipeAnn,int  **pipePereFils,int *** position);
void affichage();
#endif
