/*
Here is the main header. it must be included at once in all c files
*/

#define TREE_LEARNING_H_INCLUDED
// #ifndef STRUCTURE_H_INCLUDED

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

#ifndef FILE_MANAGER_H_INCLUDED
#include "./file_manager.h"
#endif

#ifndef DECISION_TREE_H_INCLUDED
#include "./decision_tree.h"
#endif

#ifndef ENTROPY_H_INCLUDED
#include "./entropy.h"
#endif

#ifndef UTILITY_H_INCLUDED
#include "./utility.h"
#endif

#ifndef MAP_REDUCE_H_INCLUDED
#include "./map_reduce.h"
#endif

#ifndef PARALLEL_DECISION_TREE_H_INCLUDED
#include "./parallel_decision_tree.h"
#endif