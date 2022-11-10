#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include  "fonction_split_stdin.h"
#include  "launch_shell.h"
#include  "builtin_function.h"


#define NB_MOTS 20
#define TAILLE_MOT 20 // On suppose que les mots ne dépassent pas 20 caractères


int main () {
    /*
   int nombre_mots=0;
   char str[200] = "Tu me fais vraiment chier"; // ici str est une adresse  
   char** data=malloc(sizeof(char*)*100);
   
   if (data==NULL){
       printf("Erreur d'allocation mémoire\n");
       exit(1);
   }
   for (int i=0; i<100; i++){
       data[i]=malloc(sizeof(char)*100);
   }
   
  
   split(data,str," ",&nombre_mots);
   affiche(data,nombre_mots);
   free(data);
   return 0;
   */

    shell();
    printf("Fin du programme\n");
    return  EXIT_SUCCESS;
   
  
}
