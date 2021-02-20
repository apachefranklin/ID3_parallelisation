#include <stdlib.h>
#include <stdio.h>
#define ENTROPY_H_INCLUDED
#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
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


int entropy_general(MyString **x,MyString *y, int nb_feature, int nb_line){
    //on recupere la taille des elements du tableau
    
}