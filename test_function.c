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
    MyString **mtsring;
    //int length=sizeof(target)/sizeof(*target);
    //printf("La taille du tableau est de %d \n\n",length);
    printf("\n Ici nous allons essayer d'obtenir des informations sur un fichier \n");
    int *fileInfo=file_information("Data/data.txt",";");
    int rows=*(fileInfo+1), columns=*(fileInfo+2);
    printf("Le nombre de caractere maximale d'une ligne est %d \n",*(fileInfo));
    printf("Le nombre d'informations par ligne est %d \n",columns);
    printf("Le nombre de  lignes est %d \n\n",rows);

    Feature *labels=file_content("Data/label.txt",";");
    Feature *headers_y=file_content("Data/header.txt",";");
    MyString *labels_y=(MyString*)malloc(rows*sizeof(*labels_y));
    printf("Display of new labels\n");
    for(int i=0;i<rows;i++){
        labels_y[i]=labels[i].feature[0];
    }
    printf("\nlog2->%d\n",rows);
    double entropy=entropy_general(labels_y,rows);
    printf("\nL'entropy est de de %f\n",entropy);
    return 0;
}