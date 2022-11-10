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

    shell();
    printf("Fin du programme\n");
    return  EXIT_SUCCESS;
   
  
}
