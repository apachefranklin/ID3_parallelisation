#ifndef MAP_REDUCE_H_INCLUDED

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif
#include <pthread.h>
#define MAP_REDUCE_H_INCLUDED

/*
* Reduce funtion:
* set of key values and sums up values having the same key, 
* then find the max value.
* the  key is an attribute name and  its values are gains computted 
* for that attribute in subdatasets,
*/
void *reduce(ReducerArg *r_arg);

#endif