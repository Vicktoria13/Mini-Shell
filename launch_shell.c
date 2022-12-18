
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

#define NB_MOTS 40 // il ya 20 mots separes par des espaces
#define TAILLE_MOT 40 // On suppose que les mots ne dépassent pas 20 caractères




void test_exec(int statu, char* buffer){
    if (statu == -1)
    { // si un problème à lieu à l'exécution
        perror(buffer);
        exit(1);
    } // on affiche sa nature
}


int occurence(char* buffer,  char* test){
    //fonction qui compte le nombre d'occurence de test dans buffer et renvoie ce nombre
    int nb_occurence=0;
    int i=0;
    while (buffer[i]!='\0'){
        if ((buffer[i]==test[0])){
            nb_occurence++;
        }
        i++;
    }

    return nb_occurence;
}
    

int test_error_fork(int pid){
    //fonction qui test si le fork a bien fonctionne
    //renvoie 1 si le fork a bien fonctionne, 0 sinon
    if (pid==-1){
        printf("Erreur lors du fork\n");
        exit(1);
    }
    return 0;
}

void test_malloc(char* ptr){
    //fonction qui test si le malloc a bien fonctionne
    //renvoie 1 si le malloc a bien fonctionne, 0 sinon
    if (ptr==NULL){
        printf("Erreur d'allocation mémoire\n");
        exit(1);
    }
}



/**********************************************/

int shell_test_avec_pipe(){
    /* Ce programme marche tel que :
    1- on recupere le stdin avec fgets (fonction bloquante)
    2- On regarde s'il s'agit de commande simples (exit, pwd..). On execute alors la commande
    3- Sinon, on teste la presence de |. S'il il y a un pipe , alors, on split le stdin selon le pipe, puis selon espace
    4- On execute alors les commandes en utilisant execvp
    5- Sinon, on teste la presence de >. S'il il y a un > , alors, on split le stdin selon le >, puis selon espace
    6- On execute alors les commandes en utilisant execvp
    7- si rien de tout cela, alors on split le stdin selon espace.
    */

    

    char *buffer = malloc(NB_MOTS * sizeof(char)); // on y sotckera les commandes de l'utilisateur
    
    test_malloc(buffer);
    
    int nb_mots_apres_split=0;
    int pipe_position=0;
    int flag_caractere_spec=0;
    int test_error;

    int flag_redirection=0;
    int flag_pipe=0;
    int flag_background=0;

    FILE *res;
    char path[1035];

    printf("\nBienvenue dans le shell !\nTapez \"q\" pour quitter\n");

    while(1)

    {   
        char **data ;        

        //TRAITEMENT DE L'ENTREE UTILISATEUR----------------------------------------------------------------------
        printf("$ ");
        fgets( buffer, NB_MOTS*sizeof(char), stdin ); // on recupere le STDIN
        buffer[strlen(buffer)-1]='\0';//on supprime le dernier terme du buffer (le"\n")

        if (strcmp(buffer,"exit")==0 || strcmp(buffer,"q")==0){ // si l'utilisateur tape exit on quitte le shell
            exit(0);
        }
       
        int builtin=0; // on initialise la variable builtin à 0. Si la commande est builtin, on la passe à 1

        //TRAITEMENT DES FONCTIONS BUILTIN ----------------------------------------------------------------------

        // PWD
        if(strcmp(buffer,"pwd")==0 )
         {    builtin_pwd(&builtin); //execution de la fonction builtin pwd
         }

        else if(buffer[0]=='c' && buffer[1]=='d'){
            // on teste si la commande est cd
            if (buffer[2] == ' ')
            { // Les autres cas où on a bien "cd ..." avec ... le path
                for (int i = 3; i < strlen(buffer); i++)
                {                            // Parcourt tout le buffer après "cd " et stock la chaine de caractères dans path
                    path[i - 3] = buffer[i]; // -3 car on a 'c','d' et ' ' à enlever
                }
                if (chdir(path) != 0)
                {                                  // Change le working directory
                    perror("chdir() failed");      // En cas d'échec
                    memset(path, 0, sizeof(path)); // On réinitialise le path
                }
            }
        }

        // autre que builtin
       
        else{ // on teste la presence de | ou > dans la commande

            int test = occurence(buffer,"|"); // premiere detection du pipe

            if (test >0 ){ // il ya un ou plusieurs pipes
                flag_pipe=1;
                // on split le buffer : les | sont remplacés par des NULL
                data=pipito(buffer,&nb_mots_apres_split,&pipe_position,&flag_caractere_spec,"|"); // on split le buffer en mots separes par des espaces. Oncemmence par spliter selon le pipe
              
            }

            else if (occurence(buffer,">")>0){
                
  
                    data=pipito(buffer,&nb_mots_apres_split,&pipe_position,&flag_caractere_spec,">");
                    flag_redirection=1;
                
                
            }   

            else if((occurence(buffer,"&")>0)){
                flag_background=1;
                data=pipito(buffer,&nb_mots_apres_split,&pipe_position,&flag_caractere_spec,"&");
                affiche(data,nb_mots_apres_split); // le & est remplacé par un NULL


            }

            // a ce stade, on a soit un pipe, soit une redirection.

            if (builtin == 0) // on est pas passés par le builtin donc builtin vaut 0
            {

                if (flag_pipe == 1)
                { // si il y a minimumun un pipe : creation de 2 forks
                    int fd[2];
                    if (pipe(fd) == -1)
                    { // On cree un pipe et on verifie qu'il a bien été crée
                        return 1;
                    }

                    int nb_pipe=0;


                    pid_t pid1 = fork();
                    test_error = test_error_fork(pid1); 


                    //premier fork pour la 1ere partie

                    if (pid1 == 0)
                    { // on est dans le processus enfant numero 1
                        close(fd[0]);
                        dup2(fd[1], STDOUT_FILENO);
                        close(fd[1]);
                        
                        int status = execvp(data[0], data);
                        test_exec(status, buffer);
                        
                    }


                    int pid2 = fork();
                    test_error = test_error_fork(pid2); 

                    //------------------ Travail du 2e enfant----------------------------------//
                    if (pid2 == 0){

                   

                            dup2(fd[0], STDIN_FILENO); // On dupplique le fichier desigé par STDOUT_FILENO est remplacé par une copie
                            close(fd[0]);
                            close(fd[1]);
                            int status_code = execvp(data[pipe_position + 1], data + 1 + pipe_position); // on execute la commande apres le pipe

                            if (status_code == -1) // pipe raté
                            {
                                printf("Probleme a l'execution\n");
                                exit(1);
                            }
                        }
                    

                    //dans le pere
                    close(fd[0]);
                    close(fd[1]);

                    waitpid(pid1, NULL, 0);
                    waitpid(pid2, NULL, 0);

                    flag_pipe=0;
                    // sortie du traitement du pipe
                }

                else if (flag_redirection == 1) // si redirection
                {
                    pid_t pid1 = fork();
                    test_error = test_error_fork(pid1); // si le fork a raté on quitte le shell

                    if (pid1 == 0) // enfant
                    {
                   
                        res = freopen(data[pipe_position + 1], "w", stdout);
                        int status = execvp(data[0], data);
                        test_exec(status, buffer);
                       
                    }
                     waitpid(pid1,NULL,WSTOPPED); // on attend la fin du fils                   
                    flag_redirection = 0;
                }

                

                else {
                    //on fait un simple fork

                 
                    
                    data=pipito(buffer,&nb_mots_apres_split,&pipe_position,&flag_caractere_spec,"|"); // on separe simplement selon les espaces

                    pid_t pid1 = fork();
                    test_error = test_error_fork(pid1); // si le fork a raté on quitte le shell

                    if (pid1 == 0) // enfant
                    {                          
                        int status = execvp(data[0], data); // dernier execution du fils
                        test_exec(status, buffer);
                    }
                    if (flag_background==0){
                         waitpid(pid1,NULL,0);} // on attend la fin du fils
                    else {
                        flag_background=0;
                    }
                }
            }
            free(data);
    }
    
}
free(buffer);
fclose(res);
}
