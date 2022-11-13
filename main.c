#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include  "fonction_split_stdin.h"
#include  "launch_shell.h"
#include  "builtin_function.h"


#define NB_MOTS 20
#define TAILLE_MOT 20 // On suppose que les mots ne dépassent pas 20 caractères


// git add . && git commit -m "commit" && git push 


int main () {

    shell_test_avec_pipe();
    printf("Fin du programme\n");
    return  EXIT_SUCCESS;

/*
    int nb_mots=0;
    int pipe_position=0;

    char *buffer = malloc(NB_MOTS * sizeof(char));
    char **data = malloc(sizeof(char *) * NB_MOTS);

    if (data == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }

    for (int i = 0; i < NB_MOTS; i++)
    {
        data[i] = malloc(sizeof(char) * TAILLE_MOT);
    }

    fgets( buffer, NB_MOTS*sizeof(char), stdin ); // on recupere le STDIN // attends que l'utilisateur tape qqch
    buffer[strlen(buffer)-1]='\0';


    split(data,buffer,"|", &nb_mots);
    //A ce stade on a separer les commandes par pipe : chaque case du tab contient les commandes situés avant et après le pipe
    affiche(data,nb_mots);

    // on va resplite chaque data selon le " ". On alloue alors 
    */

   /*

    char *buffer = malloc(NB_MOTS * sizeof(char));

    fgets( buffer, NB_MOTS*sizeof(char), stdin ); // on recupere le STDIN // attends que l'utilisateur tape qqch
    buffer[strlen(buffer)-1]='\0';

    int nb_mots=0;
    int pipe_position=0;

    char**res=pipito(buffer, &nb_mots, &pipe_position);
    //A ce stade on a separer les commandes par pipe : chaque case du tab contient les commandes situés avant et après le pipe
    
    for (int i=0; i<nb_mots; i++){
        if (res[i]==NULL){
            printf("res[%d] = NULL\n",i);
        }
        else{
            printf("res[%d] = %s\n",i,res[i]);
        }
    }
    printf("fin affichage : le pipe etait a la position %d\n",pipe_position);
    free(res);
    return EXIT_SUCCESS;
    */

}
