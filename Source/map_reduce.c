#include "../Header/tree_learnng.h"
#include <pthread.h>



MapperArg* createTreeMapperArgs(Dataset *dataset, int out_of_memory){
    int size=dataset->rows;
    int nb_times=get_good_nb_threads(size,out_of_memory);
    
    MapperArg *mapsargs=(MapperArg*)malloc(nb_times*sizeof(*mapsargs));
    
    int k_counter=0; //cette variable va servir dans la recuperation des indices et des feturs du dataset
    for(int i=0;i<nb_times;i++){
        //dans cette boucle nous devons construire a chaque fois le dataset pour le mapper i
        mapsargs[i].dataset=(Dataset*)malloc(sizeof(*(mapsargs[i].dataset)));
        mapsargs[i].dataset->colnames=dataset->colnames;
        mapsargs[i].dataset->cols=dataset->cols;
        mapsargs[i].dataset->real_size=dataset->rows;

        int l=i+1;
        int test=l*out_of_memory;
        if(test>size){
            out_of_memory=size-i*out_of_memory;
        }
        mapsargs[i].dataset->rows=out_of_memory;
        Feature *_features = (Feature *)malloc(out_of_memory * sizeof(*_features));
        MyString *_targets = (MyString *)malloc(out_of_memory * sizeof(*_targets));
        int k=0;
        for(int j=i*out_of_memory;j<i*out_of_memory+out_of_memory;j++){
            _features[k] = dataset->features[j];
            strcpy(_targets[k].value, dataset->targets[j].value);
            printf("\n nous sommes deja a %d \n",j);
            k++;
        }
        mapsargs[i].dataset->features=_features;
        mapsargs[i].dataset->targets=_targets;
        mapsargs[i].weigth=((double)out_of_memory)/((double)dataset->rows);
        print_dataset(mapsargs[i].dataset);
    }   
    return mapsargs;
}

void* map_id3(void *args)
{
    MapperArg *maparg=(MapperArg*)args;
    MapOutput *mapout = (MapOutput *)malloc(sizeof(*mapout));
    
    Dataset *dataset = maparg->dataset;
    
    int cols = dataset->cols;
    
    int *information_gains = (int *)malloc(dataset->cols * sizeof(*information_gain));
    
    maparg->output = (MapOutput *)malloc(cols * sizeof(*maparg->output));
    maparg->npair=cols;
    double h_x = entropy_by_dataset(maparg->dataset);
    printf("\n\n**************________________________**********____________%f\n\n",h_x);
    //print_dataset(dataset);
    for (int i = 0; i < dataset->cols; i++)
    {
        strcpy(maparg->output[i].key.value, dataset->colnames[i].value);
        maparg->output[i].value = 0.0;
        printf("***Construction du map %i\n",i);
        if (exist_ini(i, maparg->cols_to_avoid, cols) == 0)
        {
            maparg->output[i].value =(maparg->weigth)*(information_gain(h_x, dataset, i));
            printf("\nPour la colone %s d'indice %d son gain est %f\n",maparg->output[i].key.value,i,maparg->output[i].value);
        }
    }
    printf("\n\n**************________________________**********____________\n\n");
}



Model make_parallel_tree_model(Dataset *dataset){
    
    Model tree;
    tree.attributes = malloc(dataset->cols * sizeof(MyString *));
    tree.n_attributes = dataset->cols;

    int cols_to_avoid[dataset->cols];
    for (int i = 0; i < dataset->cols; i++)
    {
        strcpy(tree.attributes[i].value, dataset->colnames->value);
        cols_to_avoid[i] = -1;
    }

    Node *noeud = (Node *)malloc(sizeof(*noeud));
    inMemomeryBuild(noeud, dataset, cols_to_avoid, dataset->cols);

    tree.root_node = *noeud;
    return tree;

}



void *reduce(ReducerArg *r_arg)
{

    int i_max=get_indice_max(r_arg->shufle->gains,r_arg->shufle->length_gains);
    r_arg->bestcol=i_max;
    r_arg->gain=r_arg->shufle->gains[i_max];
    strcpy(r_arg->key.value,r_arg->shufle->colnames[i_max].value);
}


void *shuffle(ShufleArg *s_arg)
{
    
    int length_args=s_arg->length_mapargs;
    int nbcols=s_arg->length_gains;
    s_arg->gains=(double*)malloc(nbcols*sizeof(*(s_arg->gains)));
    s_arg->colnames=(MyString*)malloc(nbcols*sizeof(*(s_arg->colnames)));
    for(int i=0;i<nbcols;i++){
        s_arg->gains[i]=0.0;
        
        strcpy(s_arg->colnames[i].value,s_arg->mapargs[0].dataset->colnames[i].value);
    }
    printf("\nwelcome in shuffle\n");
    
    for(int i=0;i<length_args;i++){
        for(int j=0;j<nbcols;j++){
            //on met a jour la colonne j        
            s_arg->gains[j]=s_arg->gains[j]+s_arg->mapargs[i].output[j].value;
        }
    }

}

/*
void *merge_map_outputs_from_map_args(ShufleArg *s_arg)
{
    //on determine la taille totale du
    s_arg->length_output = 0;
    for (int i = 0; i < s_arg->length_m_args; i++)
        s_arg->length_m_outputs += s_arg->m_args[i].npair;

    s_arg->m_outputs = malloc(s_arg->length_output * sizeof(*s_arg->m_outputs));

    int counter = 0;
    for (int i = 0; i < s_arg->length_m_args; i++)
    {
        for (int j = 0; j < s_arg->m_args[i].npair; j++)
        {
            s_arg->m_outputs[counter].value = s_arg->m_args[i].output[j].value;
            strcpy(s_arg->m_outputs[counter].key.value, s_arg->m_args[i].output[j].key.value);
            counter++;
        }
    }
}

*/

