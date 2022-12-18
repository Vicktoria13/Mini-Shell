#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include  "fonction_split_stdin.h"
#include  "launch_shell.h"
#include  "builtin_function.h"


#define NB_MOTS 20
#define TAILLE_MOT 20 // On suppose que les mots ne dépassent pas 20 caractères


// git add . && git commit -m "commit" && git push 

/*
@ version 1.0
@ Auteur : Victoria Nguyen Et Matthieu sysouvanh
@ Date : 10/12/2022
@ Description : Programme qui permet de lancer un shell dans un terminal
@ Paramètres : aucun
@ Valeur de retour : 0 si le programme s'est bien déroulé, 1 sinon
*/

int main () {
    /*
    @ Fonction principale du programme
    @ Paramètres : aucuN
    */

    shell_test_avec_pipe();
    printf("Fin du programme\n");
    return  EXIT_SUCCESS;

}
