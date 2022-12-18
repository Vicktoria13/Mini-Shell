#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_MOTS 40
#define TAILLE_MOT 40 // On suppose que les mots ne dépassent pas 20 caractères


void affiche(char* tab[], int nb_mots){
    /*
    prends un tableau double entrée et affiche les éléments
    taille est le nombre d'éléments à afficher

    si l'élément est NULL, on affiche NULL et on continue
    */
    
    printf("Entree affiche du tableau 2D : il y a %d cases a affiher \n",nb_mots);
    for (int i=0; i<nb_mots; i++){
        if (tab[i]==NULL){
            printf("res[%d] = NULL\n",i);
        }
        else{
            printf("res[%d] = %s\n",i,tab[i]);
        }
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



char** allocation_tableau_char(int nb_mots,int taille_mot){
     char **data = malloc(sizeof(char *) * nb_mots);

        if (data == NULL)
        {
            printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        for (int i = 0; i < nb_mots; i++)
        {
            data[i] = malloc(sizeof(char) * taille_mot);
        }
        return data;

}



// fonction a lancer pour
char** pipito(char* buffer, int* nb_mots,int* position_du_null, int*flag_pipe,char*fisrt_separator){ //Split la chaine de caractère du buffer qui sont séparé par character_separator et met chaque mot dans un tableau
    
    // en entrée : un buffer, un pointeur sur le nombre de mots, un pointeur sur la position du NULL
    // en sortie : un tableau de pointeurs de pointeurs de caractères contentant les mots du buffer séparés par des ESPACES : les pipes sont remplacées par des NULL
    // et la position du NULL est mise à jour pour l'execvp.
    
   // La fonction opère deux splits : cependant si le premier split

    char** tableau_premier_split = allocation_tableau_char(NB_MOTS,TAILLE_MOT); // on alloue un tableau de pointeurs de pointeurs de caractères
    char** tableau_second_split = allocation_tableau_char(NB_MOTS,TAILLE_MOT);
    int nb_mots_premier_split=0;

    split(tableau_premier_split,buffer,fisrt_separator, &nb_mots_premier_split); // on split le buffer selon les pipes


    int pos_current_tableau_second_split=0;
    int nb_cases_finales_remplies=0;
    
    if (nb_mots_premier_split > 1){
        // il y a des pipes
        *flag_pipe=1;
        for (int i = 0; i < nb_mots_premier_split; i++)
        { // on parcourt le tableau_premier_split
            // on traite chaque 1er case du tableau_premier_split

            char *strtoken = strtok(*(tableau_premier_split + i), " "); // Séparation d'un mot du buffer jusqu'à un espace

            while (strtoken != NULL)
            {
                strcpy(tableau_second_split[pos_current_tableau_second_split], strtoken);
                strtoken = strtok(NULL, " "); // Accès au token suivant
                pos_current_tableau_second_split++;
                nb_cases_finales_remplies++;
            }

            *(tableau_second_split + pos_current_tableau_second_split) = NULL; // on met un NULL à la place du pipe

            if (i == 0) //dans le cas de fin de traitement de la 1ere case, cest la que se situe le 1er pipe donc le 1er NULL
           
            {
                *position_du_null = pos_current_tableau_second_split; // on met à jour la position du NULL
            }

            pos_current_tableau_second_split++; // on passe à la case suivante
            nb_cases_finales_remplies++;
        }
    }  

    else{
        // il n'y a pas de pipe
        *flag_pipe=0;
        split(tableau_second_split,buffer," ", &nb_cases_finales_remplies);
        tableau_second_split[nb_cases_finales_remplies] = NULL; // on met le dernier argument a NULL pour execvp
        nb_cases_finales_remplies++;
        
    }
    *nb_mots=nb_cases_finales_remplies; // on met à jour le nombre de mots
    
    free(tableau_premier_split);
    return tableau_second_split;
}


