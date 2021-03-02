#ifndef PARALLEL_DECISION_TREE_H_INCLUDED

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

#define PARALLEL_DECISION_TREE_H_INCLUDED

void test_parallel_decision_tree(ShufleArg sarg);

/**
 * Cette fonction permet de calculer le meilleur split
 * D'un dataset de facons distribuer en utilisant le principe 
 * Map reduce
*/
int findParallelBestSplit(Dataset *dataset,int *cols_to_avoid,int nb_cols,int out_of_memory);

/**
 * Cette fonction va permmettre de faire une construction parallele
 * de l'arbre de decision
 * en utilisant la fonction outMemomryBuild
*/
Model makeParallelTree(Dataset *dataset,int out_of_memory);

/**
 * Cette fonction prend en paramettre un dataset trop
 * Grand et construire de facons parallele
 * Et determine de facons parallelle la construction du sous arbre
 * @param Dataset *dataset
 * @param Node *noeud
 * @param int out_of_memory
 */
void outMemoryBuild(Node *noeud,Dataset *dataset,int *cols_to_avoid,int nb_cols,int out_of_memory);

#endif
