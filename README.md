Une application en C qui permet de jouer au jeu de petits
chevaux,chaque joueur est un processus distinct et les joueurs communiquent via des tubes.
Ce travail est essentiellement basé sur la gestion de la communication via des ​ “PIPES” ​ entre des
processus  “DISTINCTS”.

Pour chaque version du programme, il y’a un dossier portant le nom de version contenant
les dossiers suivants :
 ​ Bin​​ -> dossier contenant les exécutables compilés.
 ​ Headers​​ -> fichiers headers contenant les fctsProjet.h pour les versions qui l’utilisent .
 ​ Src ​ -> fichiers de source c et fctsProjet.c pour les versions qui l’utilisent chaque dossier

contient aussi un makefile qui permet de compiler automatiquement les différentes versions à
l’aide de la commande « make», on peut aussi supprimer automatiquement tous les fichiers objet
à l’aide de la commande « make clean ».
