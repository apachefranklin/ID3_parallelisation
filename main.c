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
    int rows=*(fileInfo+1), columns=*(fileInfo+2);

    Feature *features=file_content(dataPath,";");
    Feature *_labels=file_content("Data/label.txt",";");
    MyString *labels=(MyString*)malloc(rows*sizeof(*labels));
    Feature *_headers=file_content("Data/header.txt",";");
    
    printf("Display of new labels\n");
    for(int i=0;i<rows;i++){
        labels[i]=_labels[i].feature[0];
    }
    int rows=*(fileInfo+1), columns=*(fileInfo+2);
    return 0;
}