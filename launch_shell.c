
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonction_split_stdin.h"
#include "launch_shell.h"
#include "builtin_function.h"

#define NB_MOTS 20 // il ya 20 mots separes par des espaces
#define TAILLE_MOT 20 // On suppose que les mots ne dépassent pas 20 caractères


void shell(){


    printf("\nBienvenue dans le shell !\nTapez \"exit\" pour quitter\n");


    char* buffer=malloc(NB_MOTS*sizeof(char)); //on y sotckera les commandes de l'utilisateur


        // Double tableau pour le split sous forme de blocs de commandes

        char** data=malloc(sizeof(char*)*NB_MOTS);
   
         if (data==NULL){
             printf("Erreur d'allocation mémoire\n");
            exit(1);
        }
        for (int i=0; i<NB_MOTS; i++){
            data[i]=malloc(sizeof(char)*NB_MOTS);
   }



    // boucle principale
    while(1)
    {   int nb_mots=0;
        
   


        //TRAITEMENT DE L'ENTREE UTILISATEUR----------------------------------------------------------------------
        printf("$ ");
        fgets( buffer, NB_MOTS*sizeof(char), stdin ); // on recupere le STDIN
        buffer[strlen(buffer)-1]='\0';//on supprime le dernier terme du buffer (le"\n")
        printf("buffer: %s\n",buffer);

        //separation des mots des commandes
       

        int builtin=0; 

        //TRAITEMENT DES FONCTIONS BUILTIN ----------------------------------------------------------------------

        if(strcmp(buffer,"pwd")==0)
         {      
                builtin_pwd(&builtin);
         }
         

        
       
         
        

        //TRAITEMENT DU RESTE DES FONCTIONS ---------------------------------------------------------------------------------

        if (builtin==0){
            printf("buffer: %s\n",buffer);
            split(data,buffer," ",&nb_mots);
            printf("il y a %d mots\n",nb_mots);

            pid_t pid1=fork();


            if(pid1==0)
            {//on est dans le processus enfant

            // on remplit le tableau vecteur d'arguments :
                char* tab[nb_mots+1];

                for (int k=0;k<nb_mots;k++){
                    tab[k]=data[k];
                     }
                tab[nb_mots]=NULL;

                int status = execvp(tab[0],tab);
             
                if(status==-1){ //si un problème à lieu à l'exécution
                    perror(buffer);
                    exit(1);}//on affiche sa nature  
                    
            }

             wait(NULL); // On attend que l'enfant execute

            
             
        }
        
        
    }
    free(data);

    
}
