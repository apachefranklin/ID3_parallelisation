#include <stdlib.h>
#include <stdio.h>
#ifndef STRUCTURE_H_INCLUDED
#include "Header/entropy.h"
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
    //int length=entropy_general(target2,100,100);
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

    MyString **mtsring2=file_content("Data/data.txt",";");
    for(int i=0;i<=rows;i++){
        printf("%d ->",i);
        for(int j=0;j<=columns;j++){
            printf("%s-",mtsring2[i][j].value);
        }
        printf("\n");
    }
    
    return 0;
}