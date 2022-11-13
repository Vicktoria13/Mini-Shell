#ifndef FONCTION_SPLIT_H
#define FONCTION_SPLIT_H


char** allocation_tableau_char(int nb_mots,int taille_mot);

void affiche(char* tab[], int nb_mots);

void split(char** tab,char* buffer,char* character_separator, int* nb_mots);//split la chaine de caractère du buffer qui sont séparé par character_separator et met chaque mot dans un tableau

char** pipito(char* buffer, int* nb_mots,int* position_du_null,int*flag_pipe);

#endif