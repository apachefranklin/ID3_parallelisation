#include "../Header/tree_learnng.h"


int findParallelBestSplit(Dataset *dataset,int *cols_to_avoid,int nb_cols,int out_of_memory){
    int rows = dataset->rows, cols = dataset->cols;
    //determination du nombre de threads
    int nb_threads=get_good_nb_threads(rows,out_of_memory);
    pthread_t *threads_list=(pthread_t*)malloc(nb_threads*sizeof(*threads_list));
    //creons les differents mapargs
    MapperArg *mapargs=createTreeMapperArgs(dataset,out_of_memory);
    //maintenant que nous avons les differents mappargs
    //affectons chaqu'un a un threads
    for (int i=0;i<nb_threads;i++){
        mapargs[i].cols_to_avoid=cols_to_avoid;
        pthread_create(&threads_list[i],NULL,map_id3,&mapargs[i]);
    }
    //une fois ceci fait nous faisons des pthreads join pour attendre que le processus se termine
    for(int i=0;i<nb_threads;i++){
        pthread_join(threads_list[i],NULL);
    }
/*
   for(int i=0;i<nb_threads;i++){
        printf("\n In maparg %i we have the following gain \n-------------\n",i);
        for (int j=0;j<dataset->cols;j++){
            printf("Le gain de la colone %s est %f\n",mapargs[i].output[j].key.value,mapargs[i].output[j].value);
        }
        printf("\n In we have the following gain \n-------------\n");
    } */

    //cette phase terminé passons a l'etape du shuffle
    //creons d'abord un objet ShuffleArg*

    ShufleArg* shuarg=(ShufleArg*)malloc(sizeof(*shuarg));
    shuarg->mapargs=mapargs;
    shuarg->length_mapargs=nb_threads;
    shuarg->length_gains=cols;

    //printf("\nLength of map args is %d\n",shuarg->length_mapargs);
    //merge_map_outputs_from_map_args(shuarg);

    printf("\n shuffle\n");
    shuffle(shuarg);
    
    //now we nedd to call reduce
    ReducerArg *reducearg=(ReducerArg*)malloc(sizeof(*reducearg));
    reducearg->shufle=shuarg;
    reduce(reducearg);
    printf("La meilleur cle est %s et son gain est %f\n",reducearg->key.value,reducearg->gain);
    return reducearg->bestcol;
}

void outMemoryBuild(Node *noeud,Dataset *dataset,int *cols_to_avoid,int nb_cols,int out_of_memory){
    int rows = dataset->rows, cols = dataset->cols;
    MyString *colnames = dataset->colnames;
    MyString *targets = dataset->targets;

    //map reduce phase process in findParallelBestSplit
    int best_col = findParallelBestSplit(dataset, cols_to_avoid, nb_cols,out_of_memory);
    Feature uniques = get_unique_elementF(dataset, best_col);
    
    int nbuniques = uniques.id;
    strcpy(noeud->name, colnames[best_col].value);
    Dataset **dataset_split = (Dataset **)malloc(nbuniques * sizeof(*dataset_split));
    noeud->branches = (MyString *)malloc(nbuniques * sizeof(*(noeud->branches)));
    noeud->fils = (Node *)malloc(nbuniques * sizeof(*(noeud->fils)));
    noeud->length = nbuniques;

    printf("\n\nLa meilleur colone *%s* contient *%d* nombres d'elt unique \n", colnames[best_col].value, uniques.id);
    int stop = 0;
    for (int i = 0; i < nbuniques; i++)
    {
        dataset_split[i] = dataset_col_and_val(dataset, best_col, uniques.feature[i].value);
        strcpy(noeud->branches[i].value, uniques.feature[i].value);
        noeud->fils[i].prediction = 0;
        stop = stoppingCriteria(dataset_split[i]);
        if (stop == 1)
        {
            puts("\n--------------------------------------------------------\n");
            printf("La valeur predit est: %15s\n", dataset_split[i]->targets[0].value);
            print_dataset(dataset_split[i]);
            puts("\n--------------------------------------------------------\n");
            /*
                on decide ici que le noeud fils correspondant
                a i est une prediction et son nom va etre le target
                de notre arbre 
            */
            strcpy(noeud->fils[i].name, dataset_split[i]->targets[0].value);
            noeud->fils[i].prediction = 1; //ce noeud est une prediction
        }
        else
        {
            int to_ingore[cols];
            for (int k = 0; k < cols; k++)
            {
                to_ingore[k] = cols_to_avoid[k];
                if (k == best_col)
                {
                    to_ingore[k] = best_col;
                }
            }
            if(dataset_split[i]->rows>out_of_memory){
                outMemoryBuild(&(noeud->fils[i]),dataset_split[i],to_ingore,nb_cols,out_of_memory);
            }
            else{
                inMemomeryBuild(&(noeud->fils[i]), dataset_split[i], to_ingore, nb_cols);
            }
            
        }
    }
}

Model makeParallelTree(Dataset *dataset,int out_of_memory){
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

    outMemoryBuild(noeud, dataset, cols_to_avoid, dataset->cols,out_of_memory);

    tree.root_node = *noeud;
    return tree;
}

/*
void test_parallel_decision_tree(ShufleArg sf_arg)
{
    //test shufle
    // ShufleArg sf_arg;
    // int ninput = 6;
    // sf_arg.m_outputs = malloc(ninput * sizeof(*sf_arg.m_outputs));
    // sf_arg.length_m_outputs = ninput;

    // strcpy(sf_arg.m_outputs[0].key.value, "att1");
    // sf_arg.m_outputs[0].value = 2.0;

    // strcpy(sf_arg.m_outputs[1].key.value, "att2");
    // sf_arg.m_outputs[1].value = 1.0;

    // strcpy(sf_arg.m_outputs[2].key.value, "att1");
    // sf_arg.m_outputs[2].value = 3.0;

    // strcpy(sf_arg.m_outputs[3].key.value, "att2");
    // sf_arg.m_outputs[3].value = 5.0;

    // strcpy(sf_arg.m_outputs[4].key.value, "att3");
    // sf_arg.m_outputs[4].value = 2.0;

    // strcpy(sf_arg.m_outputs[5].key.value, "att2");
    // sf_arg.m_outputs[5].value = 9.0;

    // for (int i = 0; i < sf_arg.length_m_outputs; i++)
    // {
    //     printf("\n%15s\t%15f\n", sf_arg.m_outputs[i].key.value, sf_arg.m_outputs[i].value);
    // }

    shuffle(&sf_arg);
    puts("test shufle");
    for (int i = 0; i < sf_arg.length_mapargs; i++)
    {
        printf("%15s\n", sf_arg.outputs[i].key.value);
        for (int j = 0; j < sf_arg.outputs[i].length; j++)
        {
            printf("\t%15f\n", sf_arg.outputs[i].values[j]);
        }
    }

    //test reduce

    ReducerArg r_arg;
    r_arg.id_reducer = 0;
    r_arg.inputs = sf_arg.outputs;
    r_arg.length_inputs = sf_arg.length_output;

    reduce(&r_arg);
    puts("test reduce");
    printf("%15s\t%15f\n", r_arg.key.value, r_arg.gain);
}
*/