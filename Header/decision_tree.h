#include <stdio.h>
#include <stdlib.h>
#ifndef DECISION_TREE_H_INCLUDED

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

#define DECISION_TREE_H_INCLUDED

/**
 * Cette fonction va calculer le gain d'informaion de chaque 
 * colone du dataset et ensuite 
 * retouner l'indice de la colonne ayant le meilleur gain d'information
 * @param Dataset *dataset
 * @param int cols_to_avoid[] represente la liste des colonnes a eviter dans le calcul du gain
 * @param int nb_cols  est le nombre de colonnes de cols_to_avoid
 * @return indice_best_gain
*/
int findBestSplit(Dataset *dataset, int cols_to_avoid[], int nb_cols);



/**
 * Cette fonction prend en parametre un dataset 
 * et verifie s'il est compatible a yn crictere d'arret ou bien
 * si on doit construire de nouveaux avec lui
 * Le crictere d'arret est obtenu si tout les labels sont identiques
 * @param Dataset:*dataset
 * @return 1 si le critère d'arret est respecté et 0 sinon
*/
int stoppingCriteria(Dataset *dataset);

void inMemomeryBuild(Node *noeud, Dataset *dataset, int cols_to_avoid[], int nb_cols);

/**
 * this function predicts the tagret of a given feature,
 * using the Tree rooted in node.
 * @param Node root node of an aborescence 
 * @param  Mystring * feature: the feature line.
 * @param attr_names *  name of attributes
 * @param n_attr
 * @return Mysting * the predicted target
*/
MyString predict_from_feature(Node node, MyString *feature, MyString *attr_names, int n_attr);

Vector predict_from_dataset(Model model, Dataset dst);

/**
 * Cette fonction prend un noeud et ressort sa description
 * Dans un fichier texte
 * Le but ici est de pouvoir reconstruire l'arbre de decision obtenu en faisant
 * une description soit dans un fichier txt soit dans fichier xml
 * @param Node:Noeud
 * @param FIlE *outputfile un pointeur vers le fichier  de sorties
 * @param int decalage est la variable qui permet de connaitre les indentensions qu'ils faut inserer
 * @return description.txt ou description.xml
*/
void decisionTreeDescription(Node *noeud, FILE *outputfile, char *branche_name, int branche_index, int if_root, int decalage);
Model make_tree_model(Dataset *dataset);


void test_decision_tree();
#endif