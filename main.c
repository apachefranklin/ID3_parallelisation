#include <stdlib.h>
#include <stdio.h>
#ifndef STRUCTURE_H_INCLUDED
#include "Header/entropy.h"
#endif
#ifndef FUNCTION_H_INCLUDED
#include "Header/function.h"
#endif
#ifndef ENTROPY_H_INCLUDED
#include "Header/entropy.h"
#endif

#ifndef FILE_MANAGER_H_INCLUDED
#include "Header/file_manager.h"
#endif

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
    Feature uniques=get_unique_elementF(features,1,rows);
    printf("\n_____________________________________________\n\n");
    
    for(int i=0;i<uniques.id;i++){
        printf("%s :: ",uniques.feature[i].value);
    }
    
    int nb_unique2=nb_times_inF(features,uniques.feature[0].value,1,rows);
    Feature *testcut=dataset_col_and_val(&dataset,1,uniques.feature[0].value);
    printf("\n_____________________________________________\n\n");
    printf("Nb unique = %d\n\n",nb_unique2);
    for(int i=0;i<nb_unique2;i++){
        for(int j=0;j<cols;j++)
        printf("%s::",testcut[i].feature[j].value);
        printf("\n\n");
    }
    printf("\n_____________________________________________\n\n");
    //Dataset *toreturn={testcut,colnames,labels,nb_unique2,cols};
    print_dataset(testcut,nb_unique2,cols);
    return 0;
}