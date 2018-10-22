#ifndef fCTSPROJETS_H
#define fCTSPROJETS_H
void closeDescripteurFils(int i, int processNumber, int **pipeAnn, int **pipePereFils, int pipeFilsPere[2]);
void closeDescripteurPere(int processNumber, int **pipePereFils, int pipeFilsPere[2]);
void ecriturePereFils(int processNumber, int val, int **pipePereFils);
void ecritureFilsPere(int val, int pipeFilsPere[2]);
int saisirNbFils();
int **creationPipe(int processNumber);
void envoiFilsFils(int val, int i, int **pipeAnn);
int receptionFilsFils(int i, int processNumber, int **pipeAnn);
int lectureDuPere(int descr);
int lectureDuFils(int descr);

#endif