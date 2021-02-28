#ifndef FILE_MANAGER_H_INCLUDED

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

#define FILE_MANAGER_H_INCLUDED

/*
    Cette fonction retourne le nombre d'element de ligne que contient le fichier
    En seconde position retourne le nombre de caractere max d'une line
    @param char path[100]: est le chemin du fichier
    @param char separator: est le separateur qui va etre utiliser a fin de determiner le nombre d'information par ligne
    @return [nb_max_line_size,nb_line_of_file,nb_information_per_line]
*/
int* file_information(char path[100],char sep[]);


/*
 * Cette fonction va ouvrir un fichier comme s'il s'agissait d'un fichier
 * elle va retourner un tableau a 2 dimension donc les lignes seront les 
*/
Feature* file_content(char path[100],char sep[]);


#endif