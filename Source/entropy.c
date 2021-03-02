#include "../Header/tree_learnng.h"

double entropy_general(MyString *y,int y_size,int real_size)
{
    //on recupere la taille des elements du tableau
    //printf("\n--Welcome to entropy function --\n");
    char temp[100];
    double lines = (double)y_size, nb_times, frequence = 0.0, entropy = 0.0;
    Feature uniquesd = get_unique_element(y, y_size);
    for (int i = 0; i < uniquesd.id; i++)
    {
        strcpy(temp, uniquesd.feature[i].value);
        nb_times = (double)nb_times_in(temp, y, y_size);
        frequence = nb_times / y_size;
        frequence = -(frequence * log2(frequence));
        entropy += frequence;
    }

    return entropy;
}

double entropy_by_dataset(Dataset *dataset)
{
    return entropy_general(dataset->targets, dataset->rows,dataset->real_size);
}

double *entropy_by_column_and_val(Dataset *dataset, int col_index, char *value)
{
    double entropy_by_val = 0.0;
    Feature *features = dataset->features;
    MyString *labels = dataset->targets;
    int rows = dataset->rows;
    MyString column[rows];
    MyString row_for_val[rows];
    MyString labels_for_val[rows];
    /**
     * on va d'abord commencer par recuperer tous les elements
     * de la colonnes
    */
    //printf("\n Recuperation de la colonne \n");
    int size_for_val = 0;
    for (int i = 0; i < rows; i++)
    {
        strcpy(column[i].value, features[i].feature[col_index].value);
        //printf("%s && %s \n",column[i].value,value);
        if (strcmp(column[i].value, value) == 0)
        {
            strcpy(labels_for_val[size_for_val].value, labels[i].value);
            size_for_val++;
        }
        //printf("c-%d -> %s\n",i,column[i].value)
    }
    //printf("Le size la est %d\n",size_for_val);
    entropy_by_val = entropy_general(labels_for_val, size_for_val,dataset->real_size);
    //printf("Yo les gars %f\n",entropy_by_val);
    double *toreturn = (double *)malloc(4 * sizeof(*toreturn));
    toreturn[0] = entropy_by_val;
    toreturn[1] = (double)size_for_val;
    toreturn[2] = ((double)size_for_val) / rows;
    toreturn[3] = toreturn[2] * entropy_by_val;

    return toreturn;
}

double information_gain(double h_x, Dataset *dataset, int col_index)
{
    Feature *features = dataset->features;
    MyString *labels = dataset->targets;
    int rows = dataset->rows;
    double gain = 0.0;
    MyString colmun[rows];
    char value[100];
    //printf("\n\n________________________________________________%d\n",col_index);
    for (int i = 0; i < rows; i++)
    {
        strcpy(colmun[i].value, features[i].feature[col_index].value);
    }
    Feature unique_elts = get_unique_element(colmun, rows);
    double somme = 0.0;
    for (int i = 0; i < unique_elts.id; i++)
    {
        strcpy(value, unique_elts.feature[i].value);
        //printf("\n%s->%d\n",value,col_index);
        double *hc = entropy_by_column_and_val(dataset, col_index, value);
        //printf("\n H=%f,NBELT=%f,rapport=%f,H*R=%f\n",hc[0],hc[1],hc[2],hc[3]);
        somme += ((hc[1] / rows) * hc[0]);
    }
    return h_x - somme;
}
