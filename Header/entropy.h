#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define ENTROPY_H_INCLUDED
#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

#ifndef FUNCTION_H_INCLUDED
#include "function.h"
#endif


/**
 * Cette fonction prend calcule l'entropy sur une portion du jeu de donnees
 * Cette portion peut etre total ou bien elle partiel
 * @author apache
 * @param **x qui represente l'ensemble des features Categoriel
 * @param *y qui represente l'ensemble des labels categoriel
 * @param nb_line qui represente ici le nombre line de notre jeu de donnees
 * @param nb_feature qui est le nombre d'attribut
 * @return float entropy (Base sur l'algorithme ID3)
**/


double entropy_general(MyString *y,int nb_line){
    //on recupere la taille des elements du tableau 
    printf("\n--Welcome to entropy function --\n");
    
    char temp[100];
    double lines=(double)nb_line,nb_times,frequence=0.0,entropy=0.0;
    FeatureLine *uniquesd=get_unique_element(y,nb_line);
    for(int i=0;i<uniquesd->id;i++){
        strcpy(temp,uniquesd->feature[i].value);
        nb_times=(double)nb_times_in(temp,y,nb_line);
        frequence=nb_times/nb_line;
        frequence=-(frequence*log2(frequence));
        entropy+=frequence;
    }
   
    
    return entropy;
}