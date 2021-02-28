#include "../Header/tree_learnng.h"


int findBestSplit(Dataset *dataset,int cols_to_avoid[],int nb_cols){
    int rows=dataset->rows,cols=dataset->cols;
    double table_inf_gain[cols];
    //obtention de l'entropy general du dataset
    double hx=entropy_by_dataset(dataset);
    for(int col_index=0;col_index<cols;col_index++){
        table_inf_gain[col_index]=-1.0;
        if(exist_ini(col_index,cols_to_avoid,nb_cols)==0){
            table_inf_gain[col_index]=information_gain(hx,dataset,col_index);
        }
    }
    int i_best_column=get_indice_max(table_inf_gain,cols);
    printf("Le meilleur gain est de **%s** et est de **%f**\n\n",dataset->colnames[i_best_column].value,table_inf_gain[i_best_column]);

    for(int j=0;j<cols;j++){
        printf("Le gain de **%s** et est de **%f**\n",dataset->colnames[j].value,table_inf_gain[j]);
    }
    return i_best_column;
}


int stoppingCriteria(Dataset *dataset){

    Feature uniques=get_unique_element(dataset->targets,dataset->rows);
    if(uniques.id==1){
        return 1;
    }
    else return 0;
}

void inMemomeryBuild(Node *noeud,Dataset *dataset,int cols_to_avoid[],int nb_cols){
    int rows=dataset->rows,cols=dataset->cols;
    MyString *colnames=dataset->colnames;
    MyString *targets=dataset->targets;
    //cette table va contenir les gains d'information de chaqu'une des colones
    //on l'initialise d'abord a -1.0 pour etre sur que les colonnes ignorer ne nous fauserrons pas 
    //les resultats

    /*
        -Step1 calcul du gain d'information pour les differentes colonnes
        -ce step represente FindBestSplit dans l'alogrithme inMemoryBuilNode
    */
    int best_col=findBestSplit(dataset,cols_to_avoid,nb_cols);

    /*
     * Maintenant nous devons obtenier les elements unique de cette colonne
     * a fin de pouvoir decider si on fait des predictions ou pas
     */
    Feature uniques= get_unique_elementF(dataset,best_col);
    int nbuniques=uniques.id;
    strcpy(noeud->name,colnames[best_col].value);
    //on va creer un ensemble de dataset correspond a chaqu'une des valeurs
    Dataset **dataset_split=(Dataset**)malloc(nbuniques*sizeof(*dataset_split));
    noeud->branches=(MyString*)malloc(nbuniques*sizeof(*(noeud->branches)));
    noeud->fils=(Node*)malloc(nbuniques*sizeof(*(noeud->fils)));
    noeud->length=nbuniques;

    printf("\n\nLa meilleur colone *%s* contient *%d* nombres d'elt unique \n",colnames[best_col].value,uniques.id);
    int stop=0;
    for(int i=0;i<nbuniques;i++){
        dataset_split[i]=dataset_col_and_val(dataset,best_col,uniques.feature[i].value);
        strcpy(noeud->branches[i].value,uniques.feature[i].value);
        //print_dataset(dataset_split[i]);
        noeud->fils[i].prediction=0; 
        /*
            maintenant que nous connaissons le jeu de donnees
            associe a la valeur courante nous devons verifier si
            on peut produire une prediction avec ou a defaut construire un autre arbre
        */
       stop=stoppingCriteria(dataset_split[i]);
       if(stop==1){
            /*
                on decide ici que le noeud fils correspondant
                a i est une prediction et son nom va etre le target
                de notre arbre 
            */
           strcpy(noeud->fils[i].name,dataset_split[i]->targets[0].value);
           noeud->fils[i].prediction=1; //ce noeud est une prediction
        }
        else {
            /**
             *  Maintenant que cette variable offre encore des choix de decision
             * nous devons creer une sous liste des colonnes a ne pas exploite pour 
             * cette sous section en y ajoutant la colonne best_col
             */
            int to_ingore[cols];
            for(int k=0;k<cols;k++){
                to_ingore[k]=cols_to_avoid[k];
                if(k==best_col){
                    to_ingore[k]=best_col;
                }
            }

            inMemomeryBuild(&(noeud->fils[i]),dataset_split[i],to_ingore,nb_cols);
        }
    }

    /*
    for(int i=0;i<nbuniques;i++){
        stop=stoppingCriteria(dataset_split[i]);
        printf("---->\nPour la valeur la valeur %s le stopping criteria ",uniques.feature[i].value);
        if(stop==1){
            
                on decide ici que le noeud fils correspondant
                a i est une prediction et son nom va etre le target
                de notre arbre 
            
           strcpy(noeud->fils[i].name,dataset_split[i]->targets[0].value);
           noeud->fils[i].prediction=1; //ce noeud est une prediction
            printf("est respecté\n");
        }
        else {printf("n'est pas respecté\n");}
        print_dataset(dataset_split[i]);
    }
    //maintenant que nous avons les datasets pour chaque valeur de la meilleure colonne
    */
    
}


Dataset *findPrediction(Dataset *datatset){
    Dataset *dataset=(Dataset*)malloc(sizeof(*dataset));

    return dataset;
}