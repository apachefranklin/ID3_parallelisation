#include "./Header/tree_learnng.h"

int main(){
    char dataPath[]="Data/data.txt";
    char headerPath[]="Data/header.txt";
    char labelsPath[]="Data/label.txt";
    int *fileInfo=file_information(dataPath,";");
    int rows=*(fileInfo+1), cols=*(fileInfo+2);

    Feature *features=file_content(dataPath,";");
    Feature *_labels=file_content("Data/label.txt",";");
    MyString *labels=(MyString*)malloc(rows*sizeof(*labels));
    Feature *_headers=file_content("Data/header.txt",";");
    MyString *colnames=(MyString*)malloc(rows*sizeof(*colnames));
    
    //mise des labels dans une structure MyString
    for(int i=0;i<rows;i++)labels[i]=_labels[i].feature[0];
    //mise des headers dans une structure Mystring*
    for(int i=0;i<cols;i++) colnames[i]=_headers[i].feature[0];
    Dataset dataset={features,colnames,labels,rows,cols};
    //test de la fonction get_unique by_feature list
    Feature uniques=get_unique_elementF(&dataset,1);
    printf("\n_____________________________________________\n\n");
    
    for(int i=0;i<uniques.id;i++){
        printf("%s :: ",uniques.feature[i].value);
    }
    
    int nb_unique2=nb_times_inF(&dataset,uniques.feature[0].value,1);
    Dataset *testcut=dataset_col_and_val(&dataset,1,uniques.feature[0].value);
    printf("\n_____________________________________________\n\n");
    printf("Nb unique = %d\n\n",nb_unique2);
    for(int i=0;i<nb_unique2;i++){
        for(int j=0;j<cols;j++)
        printf("%s::",testcut->features[i].feature[j].value);
        printf("\n\n");
    }
    printf("\n1_____________________________________________1\n\n");
    print_dataset(testcut);
    printf("\n\n**Entropy test ***\n");
    double hx=entropy_general(labels,rows);
    double hx2=entropy_by_dataset(&dataset);
    printf("entropy = %f\n",hx);
    printf("entropy by dataset = %f\n",hx2);

    printf("\n\n**** Maintenant nous passons a la construction de l'arbre *** \n\n");
    
    Node *noeud=(Node*)malloc(sizeof(*noeud));
    int cols_to_avoid[cols];
    for(int i=0;i<cols;i++) cols_to_avoid[i]=-1;
    inMemomeryBuild(noeud,&dataset,cols_to_avoid,cols);

    FILE *outputtree=fopen("Output/output_tree.xml","w");
    decisionTreeDescription(noeud,outputtree,"",0,1,0);
    fclose(outputtree);
    return 0;
}
