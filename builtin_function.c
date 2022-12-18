#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void builtin_pwd(int* builtin){
    

    char directory[200];
    char* status = getcwd(directory,sizeof(directory));
    printf("%s\n", directory);
    *builtin=1; // flag pour savoir qu'on est dans le builtin

}

void builtin_cd(char** data,int* builtin){
    //ici data[1]= *data+1 represente le path
    // data[0]= *data est le mot cd
    if (data[1]==NULL){
        printf("cd: no arguments\n");
    }
    else{
        int status = chdir(data[1]);
        if (status==-1){
            printf("cd: no such file or directory: %s\n",data[1]);
        }
    }
    *builtin=1;
}