#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void affiche(char* tab[], int nb_mots){
    /*
    prends un tableau double entrée et affiche les éléments
    taille est le nombre d'éléments à afficher
    */
    
    printf("Entree affiche du tableau 2D\n");
    for (int i=0; i<nb_mots; i++){
        //printf("%s\n", tab[i]); ou equivalent
        printf("%s\n", *tab);
        *tab++;
        
    }
    
    
}


void split(char** tab,char* buffer,char* character_separator, int* nb_mots){ //Split la chaine de caractère du buffer qui sont séparé par character_separator et met chaque mot dans un tableau
    int i=0;
    char* strtoken = strtok(buffer,character_separator); //Séparation d'un mot du buffer jusqu'à un espace
    while(strtoken !=NULL){ //Parcourt tout le buffer pour récupérer chaque token
        strcpy(tab[i],strtoken); //Copie chaque token dans le tableau
        strtoken = strtok(NULL,character_separator); //Accès au token suivant
        i++;
    }
    *nb_mots=i;
}

void split_avec_reconnaissance_pipe(char** tab,char* buffer,char* character_separator, int* nb_mots){ //Split la chaine de caractère du buffer qui sont séparé par character_separator et met chaque mot dans un tableau
    int i=0;
    char* strtoken = strtok(buffer,character_separator); //Séparation d'un mot du buffer jusqu'à un espace
    while(strtoken !=NULL){ //Parcourt tout le buffer pour récupérer chaque token
        strcpy(tab[i],strtoken); //Copie chaque token dans le tableau
        strtoken = strtok(NULL,character_separator); //Accès au token suivant
        i++;
    }
    *nb_mots=i;
}