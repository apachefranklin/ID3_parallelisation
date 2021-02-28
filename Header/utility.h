#ifndef UTILITY_H_INCLUDED

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

#define UTILITY_H_INCLUDED


/**
 * Prend une liste de feature en parametre et renvoies 
 * les elements unique d'une colonne donnee
 * @return [feature] ou id represente le nombre d'element unique
**/
Feature get_unique_elementF(Dataset *dataset,int col_index);


/**
 * cette fonction prends en parametre un ensemble
 * d'elements et retourne la liste des elements unique
 * 
 */
Feature get_unique_element(MyString elts[],int nbelements);

/**
 * Fonction qui prend un enmble de feature et retourne uniquement
 * La colone de l'index toujours sours forme de liste de features
 * @param Feature feature est la liste des feature
 * @param int col_index est la colone qu'on veut exraire de notre liste de feature
 * @param int rows est le nombre de ligne de notre liste de features
 * @return Feature *features
 */
Feature* get_feature_column(Dataset *dataset,int col_index);

/**
 * Retroune le nom de fois que elt apparait dans list
 * 
 * @param char elt
 * @param MyString list
 * @param int nb_elt
 */ 
int nb_times_in(char elt[],MyString list[],int nb_elt);


/**
 * Retourne le nombre de fois qu'un entier apparait dans une liste
 */
int nb_times_inI(int elt,int list[],int nb_elt);


/**
 * Cette fonction retourne le nombre de fois qu'un element
 * apparait dans une colone d'une liste de feature 
 * precise
 */
int nb_times_inF(Dataset *dataset,char elt[],int col_index);


/**
 * Cette fonction prend en pametre un dataset
 * et retoune un autre dataset composer unquement 
 * des lignes ou la valeur de la colonne col_index veaut val
*/

Dataset* dataset_col_and_val(Dataset *dataset,int col_index,char val[]);


 /**
  * Cette fonction prend en prametre un dataset 
  * et l'affiche a l'ecran
*/

void print_dataset(Dataset *dataset);

/**
 * cette fonction prend en parametre un double 
 * et verife s'il existe dans une liste 
 * de double
 * @param nb:double le nombre a chercher
 * @param list[]:double la liste de nombre ou chercher
 * @param size:int la taille de la liste de nombre
 * @return 0 ou 1 0 si pas trouvé et 1 si trouvé
*/
int exist_in(double nb,double list[],int size);



/**
 * cette fonction prend en parametre un entier
 * et verife s'il existe dans une liste d'entier
 * @param nb:int le nombre a chercher
 * @param list[]:int la liste de nombre ou chercher
 * @param size:int la taille de la liste de nombre
 * @return 0 ou 1 0 si pas trouvé et 1 si trouvé
*/
int exist_ini(int nb,int list[],int size);


/**
 * Cette foncton prend en parametre
 * un tableau et retourne l'indice de 
 * l'element maximal
 * @param table[]:double
 * @param size:int
 * @return indice_max ou table[indice_max]=max(table)
*/
int get_indice_max(double table[],int size);

/**
 * Retourne une chaine contenant le nombre de tabulation passe
 * en parametre
*/
char *getTabulation(int nb);
#endif
