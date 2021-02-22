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
    int target[]={67,89,9,87,5,6,7,9,0,10,11,23,4,5};
    int *target2=(int*)malloc(9*sizeof(int)); //reservation d'un tableau de 9 element
    printf("La valeur de ce tableau est %d \n\n",*target);
    MyString **mtsring;
    //int length=sizeof(target)/sizeof(*target);
    //printf("La taille du tableau est de %d \n\n",length);
    printf("\n Ici nous allons essayer d'obtenir des informations sur un fichier \n");
    int *fileInfo=file_information("Data/data.txt",";");
    int rows=*(fileInfo+1), columns=*(fileInfo+2);
    printf("Le nombre de caractere maximale d'une ligne est %d \n",*(fileInfo));
    printf("Le nombre d'informations par ligne est %d \n",columns);
    printf("Le nombre de  lignes est %d \n\n",rows);

    char testchaine[100];
    FILE* file=fopen("Data/data.txt","r");
    fgets(testchaine,37,file);
    fclose(file);
    printf("La premiere ligne est\n%s",testchaine);
    printf("\n \n Maintenant nous devons faire les experiences de recuperations \n \n");

    //MyString **mtsring2=file_content("Data/data.txt",";");
    FeatureLine *features=file_content("Data/data.txt",";");
    for(int i=0;i<rows;i++){
        printf("%d ->",i);
        for(int j=0;j<columns;j++){
            printf("%s-",features[i].feature[j].value);
        }
        printf("\n");
    }
    printf("\n \n");
    FeatureLine *labels=file_content("Data/label.txt",";");
    FeatureLine *headers_y=file_content("Data/header.txt",";");
    MyString *labels_y=(MyString*)malloc(rows*sizeof(*labels_y));
    printf("Display of new labels\n");
    for(int i=0;i<rows;i++){
        labels_y[i]=labels[i].feature[0];
        printf("%s \n",labels_y[i].value);
    }
    fflush(stdin);
    printf("Affichage des labels uniques %d \n",rows);
    FeatureLine uniquelabels=get_unique_element(labels_y,rows);
    printf("\n Nous sortons de cette fonction \n");
    char bjr[100];
    for (int i=0;i<uniquelabels.id;i++){
        printf("%s \n",uniquelabels.feature[i].value);
        strcpy(bjr,uniquelabels.feature[i].value);
        printf("%s vient dans le jeu de donnees %d fois \n",bjr,nb_times_in(bjr,labels_y,rows));
    }
    printf("\nlog2->%d\n",rows);
    double entropy=entropy_general(labels_y,rows);
    printf("\nL'entropy max est de de %f\n",entropy);
    FeatureLine *test_col=get_feature_column(features,1,rows);

    MyString *test_col2=(MyString*)malloc(rows*sizeof(*test_col2));
    printf("Display of test col\n");
    for(int i=0;i<rows;i++){
        strcpy(test_col2[i].value,test_col[i].feature[0].value);
        printf("%s \n",test_col2[i].value);
    }
    FeatureLine uniquefor_col=get_unique_element(test_col2,rows);

    double* entropy_2=entropy_by_column_and_val(features,1,labels_y,uniquefor_col.feature[1].value,rows,columns);
    
    printf("L'entropy de la colone i=%d pour la valeur v=%s est H=%f",0,uniquefor_col.feature[0].value,entropy_2[0]);
    return 0;
}