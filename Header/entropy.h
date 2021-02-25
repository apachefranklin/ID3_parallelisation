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
    FeatureLine uniquesd=get_unique_element(y,nb_line);
    for(int i=0;i<uniquesd.id;i++){
        strcpy(temp,uniquesd.feature[i].value);
        nb_times=(double)nb_times_in(temp,y,nb_line);
        frequence=nb_times/nb_line;
        frequence=-(frequence*log2(frequence));
        entropy+=frequence;
    }
   
    
    return entropy;
}

/**
 * Cette fonction prend en entre une liste de feature
 * un index de column et une valeur de cette column ensuite
 * Calul l'entropy de cet echantillon et retourne une liste de nombre
 * ou le premier element est l'entropy et le second est la taille du sous echantillons/echantillonage toale
 * @return [entropy,rapport,entropy*rapport]
 */
double* entropy_by_column_and_val(FeatureLine *features,int col_index,MyString *labels,char *value,int rows){
    double entropy_by_val=0.0;
    MyString column[rows];
    MyString row_for_val[rows];
    MyString labels_for_val[rows];
    /**
     * on va d'abord commencer par recuperer tous les elements
     * de la colonnes
    */
   printf("\n Recuperation de la colonne \n");
   int size_for_val=0;
   for(int i=0;i<rows;i++){
        strcpy(column[i].value,features[i].feature[col_index].value);
        printf("%s && %s \n",column[i].value,value);
        if(strcmp(column[i].value,value)==0){
            strcpy(labels_for_val[size_for_val].value,labels[i].value);
            size_for_val++;
        }
        //printf("c-%d -> %s\n",i,column[i].value)
   }
   printf("Le size la est %d\n",size_for_val);
    entropy_by_val=entropy_general(labels_for_val,size_for_val);
    double *toreturn=malloc(3*sizeof(*toreturn));
    toreturn[0]=entropy_by_val;
    toreturn[1]=size_for_val/rows;
    toreturn[2]=toreturn[1]*entropy_by_val;
    return toreturn;
}

/**
 * Cette fonction calcule le gain d'information lie a une 
 * Colonne
 * Et ceci se fait sous la base.
 * @author Groupe1
 * @param double entropy_g is the general entropy for enterire datatsets
 * @param double* entropy_partiel is the entropy of different value.
 * @param int rows est le nombre d'element total de notre datasets
*/
double information_gain(double h_x,FeatureLine *features,MyString *labels,int col_index,int rows){
    double gain=0.0;
    MyString colmun[rows];
    char value[100];
    for(int i=0;i<rows;i++){
        strcpy(colmun[i].value,features[i].feature[col_index].value);
    }
    FeatureLine unique_elts=get_unique_element(colmun,rows);
    for(int i=0;i<unique_elts.id;i++){
        strcpy(value,unique_elts.feature[i].value);
        double *current_entropy=entropy_by_column_and_val(features,col_index,labels,value,rows);
    }
    return gain;
}