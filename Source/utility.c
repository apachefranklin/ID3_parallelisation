#include "../Header/tree_learnng.h"

Feature get_unique_elementF(Dataset *dataset, int col_index)
{
    //MyString uniqueelt[nbelements];
    int nbelements = dataset->rows;
    MyString *uniqueelt = (MyString *)malloc(nbelements * sizeof(*uniqueelt));
    Feature *feature;
    //MyString *uniqueelt;

    for (int i = 0; i < nbelements; i++)
    {
        strcpy(uniqueelt[i].value, " ");
    }
    int nb_unique = 0;
    int trouve = 0;
    for (int i = 0; i < nbelements; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (strcmp(dataset->features[i].feature[col_index].value, uniqueelt[j].value) == 0)
            {
                //printf("%s == %s \n",elts[i].value,uniqueelt[j].value);
                trouve = 1;
            }
        }
        if (trouve == 0)
        {
            //printf("an unique %s ->\n",elts[i].value);
            strcpy(uniqueelt[nb_unique].value, dataset->features[i].feature[col_index].value);
            nb_unique++;
        }
        trouve = 0;
    }

    Feature featuress;

    //Feature* unique2=(Feature*)malloc(nb_unique*sizeof(Feature));
    featuress.feature = uniqueelt;
    featuress.id = nb_unique;
    /*
    printf("***bonjour la fin****\n");
    
    printf("Le nombre d'elt unique est %d \n",nb_unique);
    //printf("--------\n");
    for(int i=0;i<nb_unique;i++){
        //unique2[i]=uniqueelt[2];
        printf("hu->%s -- ",features.feature[i].value);
    }
    printf("\n");
    */
    //features.feature=unique2;
    return featuress;
}

Feature get_unique_element(MyString elts[], int nbelements)
{
    //MyString uniqueelt[nbelements];
    MyString *uniqueelt = (MyString *)malloc(nbelements * sizeof(*uniqueelt));
    Feature *feature;
    //MyString *uniqueelt;

    for (int i = 0; i < nbelements; i++)
    {
        strcpy(uniqueelt[i].value, " ");
    }
    int nb_unique = 0;
    int trouve = 0;
    for (int i = 0; i < nbelements; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (strcmp(elts[i].value, uniqueelt[j].value) == 0)
            {
                //printf("%s == %s \n",elts[i].value,uniqueelt[j].value);
                trouve = 1;
            }
        }
        if (trouve == 0)
        {
            //printf("an unique %s ->\n",elts[i].value);
            strcpy(uniqueelt[nb_unique].value, elts[i].value);
            nb_unique++;
        }
        trouve = 0;
    }

    Feature features;

    //Feature* unique2=(Feature*)malloc(nb_unique*sizeof(Feature));
    features.feature = uniqueelt;
    features.id = nb_unique;
    /*
    printf("***bonjour la fin****\n");
    
    printf("Le nombre d'elt unique est %d \n",nb_unique);
    //printf("--------\n");
    for(int i=0;i<nb_unique;i++){
        //unique2[i]=uniqueelt[2];
        printf("hu->%s -- ",features.feature[i].value);
    }
    printf("\n");
    */
    //features.feature=unique2;
    return features;
}

Feature *get_feature_column(Dataset *dataset, int col_index)
{
    int rows = dataset->rows;
    Feature *features;
    features = (Feature *)malloc(rows * sizeof(*features));
    for (int i = 0; i < rows; i++)
    {
        //strcpy((*(features+i)).feature[0].value,feature[i].feature[col_index].value);
        features[i].id = dataset->features[i].id;
        features[i].feature = &(dataset->features[i]).feature[col_index];
        //printf("hello %s\n",features[i].feature[0].value);
    }
    return features;
}

int nb_times_in(char elt[], MyString list[], int nb_elt)
{
    int nb = 0;
    for (int i = 0; i < nb_elt; i++)
    {
        if (strcasecmp(elt, list[i].value) == 0)
        {
            nb++;
        }
    }
    return nb;
}

int nb_times_inI(int elt, int list[], int nb_elt)
{
    int nb = 0;
    for (int i = 0; i < nb_elt; i++)
    {
        if (elt == list[i])
        {
            nb++;
        }
    }
    return nb;
}

int nb_times_inF(Dataset *dataset, char elt[], int col_index)
{
    int nb = 0;
    int nb_elt = dataset->rows;
    for (int i = 0; i < nb_elt; i++)
    {
        if (strcasecmp(elt, dataset->features[i].feature[col_index].value) == 0)
        {
            nb++;
        }
    }
    return nb;
}

Dataset *dataset_col_and_val(Dataset *dataset, int col_index, char val[])
{
    //Feature unique_col_element=get_unique_elementF(features,col_index,dataset->rows);
    int nb_unique = nb_times_inF(dataset, val, col_index);
    //on recupere le nombre de fois que l'element viens dans la colonne
    printf("\n---Before malloc---- nb_unique=%d\n", nb_unique);
    Feature *_features = (Feature *)malloc(nb_unique * sizeof(*_features));
    MyString *_targets = (MyString *)malloc(nb_unique * sizeof(*_targets));
    //toreturn->features=_features;
    int rows = dataset->rows;
    int j = 0;

    for (int i = 0; i < rows, j < nb_unique; i++)
    {
        if (strcmp(dataset->features[i].feature[col_index].value, val) == 0)
        {
            _features[j] = dataset->features[i];
            strcpy(_targets[j].value, dataset->targets[i].value);
            j++;
        }
    }
    Dataset *toreturn = (Dataset *)malloc(1 * sizeof(*toreturn));
    toreturn->rows = nb_unique;
    toreturn->features = _features;
    toreturn->colnames = dataset->colnames;
    toreturn->targets = _targets;
    toreturn->cols = dataset->cols;

    return toreturn;
}

void print_dataset(Dataset *dataset)
{
    printf("\n***********************************************************************************************\n");
    int rows = dataset->rows, cols = dataset->cols;
    printf(" : cols");
    for (size_t i = 0; i < cols; i++)
    {
        printf("%17s ", dataset->colnames[i].value);
    }
    printf("  target\n");
    for (int i = 0; i < rows; i++)
    {
        printf("%d: id=%d", i, dataset->features[i].id);
        for (int j = 0; j < cols; j++)
        {
            printf("%17s", dataset->features[i].feature[j].value);
        }
        printf("%17s\n", dataset->targets[i].value);
    }
    printf("\n***********************************************************************************************\n");
}

int exist_in(double nb, double list[], int size)
{
    int exist = 0;
    if (size > 0)
    {
        int j = 0;
        while (j < size && exist == 0)
        {
            if (list[j] == nb)
                exist = 1;
            j++;
        }
    }
    return exist;
}

int exist_ini(int nb, int list[], int size)
{
    int exist = 0;
    if (size > 0)
    {
        int j = 0;
        while (j < size && exist == 0)
        {
            if (list[j] == nb)
                exist = 1;
            j++;
        }
    }
    return exist;
}

int get_indice_max(double table[], int size)
{
    int indice_max = 0;
    for (int i = 1; i < size; i++)
    {
        if (table[indice_max] < table[i])
        {
            indice_max = i;
        }
    }
    return indice_max;
}

char *getTabulation(int nb){
    char *to_return=(char*)malloc((nb+1)*sizeof(*to_return));
    for(int i=0;i<nb;i++) to_return[i]='\t';
    to_return[nb]='\0';
    return to_return;
}