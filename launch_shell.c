
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

    char *buffer = malloc(NB_MOTS * sizeof(char)); // on y sotckera les commandes de l'utilisateur
    
    test_malloc(buffer);
    
    int nb_mots_apres_split=0;
    int pipe_position=0;
    int flag_caractere_spec=0;
    int test_error;

    int flag_redirection=0;
    int flag_pipe=0;

    FILE *res;
    


    
    
    printf("\nBienvenue dans le shell !\nTapez \"q\" pour quitter\n");

    /**************creation pipe********************************/

    // boucle principale
    while(1)

    {   int nb_mots=0;
        char **data ;

        // Double tableau pour le split sous forme de blocs de commandes
        

        //TRAITEMENT DE L'ENTREE UTILISATEUR----------------------------------------------------------------------
        printf("$ ");
        fgets( buffer, NB_MOTS*sizeof(char), stdin ); // on recupere le STDIN
        buffer[strlen(buffer)-1]='\0';//on supprime le dernier terme du buffer (le"\n")

        if (strcmp(buffer,"exit")==0 || strcmp(buffer,"q")==0){ // si l'utilisateur tape exit on quitte le shell
            exit(0);
        }
       
        int builtin=0; 

        //TRAITEMENT DES FONCTIONS BUILTIN ----------------------------------------------------------------------
        // PWD
        if(strcmp(buffer,"pwd")==0)
         {       builtin_pwd(&builtin);}
       
        else{ // on teste la presence de | ou > dans la commande

            int test = occurence(buffer,"|"); // premiere detection du pipe
            if (test >0 ){
                printf("il y a %d pipe\n",test);
                flag_pipe=1;
                data=pipito(buffer,&nb_mots_apres_split,&pipe_position,&flag_caractere_spec,"|"); // on split le buffer en mots separes par des espaces. Oncemmence par spliter selon le pipe

                if (strcmp(*data, "cd")==0){
                     builtin_cd(data,&builtin);} // builtin passe a 1 si la fonction cd est appelée

            }

            else {
                test=occurence(buffer,">");

                if (test > 0)
                {   printf("il y a %d redirection\n",test);
                    data=pipito(buffer,&nb_mots_apres_split,&pipe_position,&flag_caractere_spec,">");
                    flag_redirection=1;
                  

                }
                
            }

            

            // TRAITEMENT DU RESTE DES FONCTIONS ---------------------------------------------------------------------------------       



            if (builtin == 0) // on est pas passés par le builtin donc builtin vaut 0
            {   

                if (flag_pipe==1) { // si il y a un pipe : creation de 2 forks
                    int fd[2];
                    if (pipe(fd) == -1)
                    { // On cree un pipe et on verifie qu'il a bien été crée
                        return 1;
                    }
                    pid_t pid1 = fork();
                    test_error = test_error_fork(pid1); 

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
                    if (pid2 == 0)
                    {
                        dup2(fd[0], STDIN_FILENO); // On duppliquele fichier desigé par STDOUT_FILENO est remplacé par une copie
                        close(fd[0]);
                        close(fd[1]);
                        execvp(data[pipe_position + 1], data + 1 + pipe_position); // on execute la commande apres le pipe
                    }
                    //dans le pere
                    close(fd[0]);
                    close(fd[1]);

                    waitpid(pid1, NULL, 0);
                    waitpid(pid2, NULL, 0);

                    flag_pipe=0;
                }


                else if (flag_redirection == 1)
                {


                    pid_t pid1 = fork();
                    test_error = test_error_fork(pid1); // si le fork a raté on quitte le shell

                    if (pid1 == 0) // enfant
                    {
                   
                        res = freopen(data[pipe_position + 1], "w", stdout);
                        int status = execvp(data[0], data);
                        test_exec(status, buffer);
                       
                    }
                     wait(NULL); // on attend la fin du fils

                    
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
                     wait(NULL); // on attend la fin du fils
                }

            }
            free(data);
    }
   
    
    
}
free(buffer);
fclose(res);
}

