#include "../Header/tree_learnng.h"

int findBestSplit(Dataset *dataset, int cols_to_avoid[], int nb_cols)
{
    int rows = dataset->rows, cols = dataset->cols;
    double table_inf_gain[cols];
    //obtention de l'entropy general du dataset
    double hx = entropy_by_dataset(dataset);
    for (int col_index = 0; col_index < cols; col_index++)
    {
        table_inf_gain[col_index] = -1.0;
        if (exist_ini(col_index, cols_to_avoid, nb_cols) == 0)
        {
            table_inf_gain[col_index] = information_gain(hx, dataset, col_index);
        }
    }
    int i_best_column = get_indice_max(table_inf_gain, cols);
    printf("Le meilleur gain est de **%s** et est de **%f**\n\n", dataset->colnames[i_best_column].value, table_inf_gain[i_best_column]);

    for (int j = 0; j < cols; j++)
    {
        printf("Le gain de **%s** et est de **%f**\n", dataset->colnames[j].value, table_inf_gain[j]);
    }
    return i_best_column;
}

int stoppingCriteria(Dataset *dataset)
{

    Feature uniques = get_unique_element(dataset->targets, dataset->rows);
    if (uniques.id == 1)
    {
        return 1;
    }
    else
        return 0;
}

void inMemomeryBuild(Node *noeud, Dataset *dataset, int cols_to_avoid[], int nb_cols)
{
    int rows = dataset->rows, cols = dataset->cols;
    MyString *colnames = dataset->colnames;
    MyString *targets = dataset->targets;
    //cette table va contenir les gains d'information de chaqu'une des colones
    //on l'initialise d'abord a -1.0 pour etre sur que les colonnes ignorer ne nous fauserrons pas
    //les resultats

    /*
        -Step1 calcul du gain d'information pour les differentes colonnes
        -ce step represente FindBestSplit dans l'alogrithme inMemoryBuilNode
    */
    int best_col = findBestSplit(dataset, cols_to_avoid, nb_cols);

    /*
     * Maintenant nous devons obtenier les elements unique de cette colonne
     * a fin de pouvoir decider si on fait des predictions ou pas
     */
    Feature uniques = get_unique_elementF(dataset, best_col);
    int nbuniques = uniques.id;
    strcpy(noeud->name, colnames[best_col].value);
    //on va creer un ensemble de dataset correspond a chaqu'une des valeurs
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
        //print_dataset(dataset_split[i]);
        noeud->fils[i].prediction = 0;
        /*
            maintenant que nous connaissons le jeu de donnees
            associe a la valeur courante nous devons verifier si
            on peut produire une prediction avec ou a defaut construire un autre arbre
        */
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
            /**
             *  Maintenant que cette variable offre encore des choix de decision
             * nous devons creer une sous liste des colonnes a ne pas exploite pour 
             * cette sous section en y ajoutant la colonne best_col
             */
            int to_ingore[cols];
            for (int k = 0; k < cols; k++)
            {
                to_ingore[k] = cols_to_avoid[k];
                if (k == best_col)
                {
                    to_ingore[k] = best_col;
                }
            }

            inMemomeryBuild(&(noeud->fils[i]), dataset_split[i], to_ingore, nb_cols);
        }
    }
}


void decisionTreeDescription(Node *noeud, FILE *outputfile, char *branche_name, int branche_index, int if_root, int decalage)
{
    //on commence d'abord par ecrire les decalages dans le fichier
    fputs(getTabulation(decalage), outputfile);
    //maintenant nous devons ecrire le noeud et ses attributs
    fprintf(outputfile, "<node name='%s' prediction='%d' frombranch='%s' index='%d'>", noeud->name, noeud->prediction, branche_name, branche_index);
    //maintenant nous devons ecrire les branches
    if (noeud->prediction == 1)
    {
        fputs("</node>\n", outputfile);
    }
    else
    {
        fprintf(outputfile, "\n%s<son>\n", getTabulation(decalage + 1));
        for (int i = 0; i < noeud->length; i++)
        {
            //on insere le nombre d'element necessaire pour faire un bon decalage
            fputs(getTabulation(decalage + 1), outputfile);
            decisionTreeDescription(&(noeud->fils[i]), outputfile, noeud->branches[i].value, i, 0, decalage + 1);
        }
        fputs(getTabulation(decalage + 1), outputfile);
        fputs("</son>\n", outputfile);
        fputs(getTabulation(decalage), outputfile);
        fputs("</node>", outputfile);
    }
}

MyString predict_from_feature(Node noeud, MyString *line, MyString *att_rnames, int n_attr)
{
    MyString pred_target;

    if (noeud.prediction == 1)
    {
        strcpy(pred_target.value, noeud.name);
        puts("matched\n");
    }
    else
    {
        int col = 0;

        //find the attribute index in the dataset
        while (col < n_attr && strcmp(att_rnames[col].value, noeud.name) != 0)
        {
            col++;
        }
        if (col >= n_attr)
        {
            printf("error! cannot find the attribute «%s» in the given row\n", noeud.name);
            exit(EXIT_FAILURE);
        }

        //find the corresponding branch
        int j = 0;
        while (j < noeud.length && strcmp(noeud.branches[j].value, line[col].value) != 0)
            j++;

        if (j >= noeud.length)
        {
            printf("error! No branch was found!\n");
            exit(EXIT_FAILURE);
        }
        printf("\t %15s : %15s\n", noeud.name, noeud.branches[j].value);

        pred_target = predict_from_feature(noeud.fils[j], line, att_rnames, n_attr);
    }
    return pred_target;
}

Vector predict_from_dataset(Model model, Dataset dst)
{
    Vector pred_targets;
    MyString pred;
    pred_targets.values = malloc(dst.rows * sizeof(*pred_targets.values));
    pred_targets.length = dst.rows;

    printf("%15s%15s", "", "PREDICTION\n");
    for (int i = 0; i < dst.rows; i++)
    {
        pred = predict_from_feature(model.root_node, dst.features[i].feature, dst.colnames, dst.cols);
        strcpy(pred_targets.values[i].value, pred.value);
        printf("%d »» expected: %15s\t obtained: %15s\n", i, dst.targets[i].value, pred.value);
    }
    printf("%15s%15s", "", "END PREDICTION\n");

    pred_targets;
}

Model make_tree_model(Dataset *dataset)
{
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


Model make_parallel_tree_model(Dataset *dataset){
    Model tree;


}