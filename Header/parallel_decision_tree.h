#ifndef PARALLEL_DECISION_TREE_H_INCLUDED

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

#define PARALLEL_DECISION_TREE_H_INCLUDED

void test_parallel_decision_tree(ShufleArg sarg);

/**
 * Cette fonction prend en entree 
 * un noeud et un dataset et retourne 
 * et construit un arbre de decision
 * @param 
*/
void map_construction(Node *node, Dataset *dataset);
#endif
