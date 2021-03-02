#ifndef ENTROPY_H_INCLUDED

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

#define ENTROPY_H_INCLUDED


/**
 * Cette fonction prend calcule l'entropy sur une portion du jeu de donnees
 * Cette portion peut etre total ou bien elle partiel
 * @param *y:int qui represente l'ensemble des labels categoriel
 * @param y_size:int le nombre d'element contenu dans *y
 * @param nb_line qui represente ici le coeffcient par le quel l'entropie sera divisise, en general il est egal=y_size
 * @param nb_feature qui est le nombre d'attribut
 * @return float entropy (Basé sur l'algorithme ID3)
**/
double entropy_general(MyString *y,int y_size,int real_size);


/**
 * Prend en parametre un dataset 
 * et retourne son entropy
 */
double entropy_by_dataset(Dataset *dataset);


/**
 * Cette est fonction l'equivalente Hxaj=v dans le calcul de l'entropy
 * Cette fonction prend en entre une liste de feature
 * un index de column et une valeur de cette column ensuite
 * Calul l'entropy de cet echantillon et retourne une liste de nombre
 * ou le premier element est l'entropy et le second est la taille du sous echantillons/echantillonage toale
 * le 3 eme est le rapport nblet/nbelttotal
 * le 4eme est entropy*rapport
 * @return [entropy,nb_elt,rapport,entropy*rapport,]
 */
double* entropy_by_column_and_val(Dataset *dataset,int col_index,char *value);

/**
 * Cette fonction calcule le gain d'information lie a une 
 * Colonne
 * Et ceci se fait sous la base.
 * @author Groupe1
 * @param double entropy_g is the general entropy for enterire datatsets
 * @param double* entropy_partiel is the entropy of different value.
 * @param int rows est le nombre d'element total de notre datasets
*/
double information_gain(double h_x,Dataset *dataset,int col_index);




#endif