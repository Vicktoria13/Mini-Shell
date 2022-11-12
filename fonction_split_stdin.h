#ifndef FONCTION_SPLIT_H
#define FONCTION_SPLIT_H




void affiche(char* tab[], int nb_mots);

void split(char** tab,char* buffer,char* character_separator, int* nb_mots);//split la chaine de caractère du buffer qui sont séparé par character_separator et met chaque mot dans un tableau

void split_avec_reconnaissance_pipe(char** tab,char* buffer,char* character_separator, int* nb_mots,int* pipe_position);
#endif