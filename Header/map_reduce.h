#ifndef MAP_REDUCE_H_INCLUDED

#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif
#include <pthread.h>
#define MAP_REDUCE_H_INCLUDED

/**
 * Ceci est la fonction map de notre apprentissage
 * Nous avons decidés de paralleliser le calcul du gain d'information
 * qui est pour la METHODE PLANET la recheche du findBestSplit()
 * @param MapperArg *args
 * @return *MapOutput
 */
void* map_id3(void *args);

/**
 * Cette fonction prends en parametre 
 * un dataset et renvois une liste 
 * de mapperargs, qu'on parsera aux differents threads et a la fonction
 * map_id3
 */
MapperArg* createTreeMapperArgs(Dataset *dataset, int out_of_memory);



/*
* Reduce funtion:
* set of key values and sums up values having the same key, 
* then find the max value.
* the  key is an attribute name and  its values are gains computted 
* for that attribute in subdatasets,
*/
void *reduce(ReducerArg *r_arg);

/*
* shuefle: the param s_arg must be  passed to merge_map_outputs_from_map_args
* before using it.
* Cette fonction va regrouper les resultats en sommant les differents gains d'informations
* 
*/
void *shuffle(ShufleArg *s_arg);

/*
* concatenates lists  of mappers output 
*/
void *merge_map_outputs_from_map_args(ShufleArg *s_arg);
#endif