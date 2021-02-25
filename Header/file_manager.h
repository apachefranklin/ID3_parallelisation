#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FILE_MANAGER_H_INCLUDED
#ifndef STRUCTURE_H_INCLUDED
#include "structure.h"
#endif

/*
    Cette fonction retourne le nombre d'element de ligne que contient le fichier
    En seconde position retourne le nombre de caractere max d'une line
    @param char path[100]: est le chemin du fichier
    @param char separator: est le separateur qui va etre utiliser a fin de determiner le nombre d'information par ligne
    @return [nb_max_line_size,nb_line_of_file,nb_information_per_line]
*/
int* file_information(char path[100],char sep[]){

   FILE* file =fopen(path,"r");
   char currentC=' ';
   char separator=sep[0];
   int nbMax=0, nbLines=0,nbCurrentLine=0,nbInfoPerLine=0;
   int *toReturn=(int*)malloc(3*sizeof(int));
   do
   {
       currentC=fgetc(file);
       if(currentC=='\n'){
           if (nbCurrentLine>nbMax){
               nbMax=nbCurrentLine;
           }
        nbCurrentLine=0;
        nbLines++;
       }

       else{
           nbCurrentLine++;
       }
       //ici nous voulons connaitre la dimension en terme de colone du tableau
       if (currentC==separator){
           if (nbLines==0)
           {
               nbInfoPerLine++;
           }
       }
   } while (currentC!=EOF);
   toReturn[0]=nbMax+1;
   toReturn[1]=nbLines+1;
   toReturn[2]=nbInfoPerLine+1;
   fclose(file);
   return toReturn;
}

/*
 * Cette fonction va ouvrir un fichier comme s'il s'agissait d'un fichier
 * elle va retourner un tableau a 2 dimension donc les lignes seront les 
*/
Feature* file_content(char path[100],char sep[]){
    FILE* file=fopen(path,"r");
    int* file_info=file_information(path,sep);
    int maxCaracters=*file_info;
    int rows=*(file_info+1);
    int columns=*(file_info+2);
    printf("Caractere max= %d \n",maxCaracters);
    printf("Nombre de lingnes = %d \n",rows);
    printf("Nombre de colones = %d \n",columns);
    /*
     * Maintenant que nous avons les parametres de la fonction fgets()
     * Nous pouvons maintenant faire des fgets et les analyser pour extraires les           informations donc nous aurons besoins
    */
    MyString **mstring=(MyString **)malloc(rows * sizeof(MyString *));
    Feature *features=(Feature *)malloc(rows*sizeof(Feature));
    //nous devons maintenant faire une allocation
    char curString[maxCaracters];
    char *token=NULL;
    char *token2=NULL;
    int j=0;
    //printf("\n Nous sommes encore dehors les gars \n");
    for(int i=0;i<rows;i++){
        token2=NULL;
        token=NULL;
        mstring[i]=(MyString*)malloc(columns*sizeof(MyString));
        fgets(curString,maxCaracters+1,file);
        size_t len=strlen(curString);
        if (len>0 && curString[len-1]=='\n')
        {
            curString[len-1]='\0';
        }
        
        //printf("%d: %s \n",i,curString);
        //maintenant nous allons analyser cette chaine a fin d'extraire les informations a l'interieur
        token=strtok(curString,sep);
        //en fonction du nombre de colone nous allons parcourir ce token
        j=0;
        while (token!=NULL)
        {
            //printf("\n-----Nous y sommes quand meme entreee-------\n");
            strcpy(mstring[i][j].value,token);
            //printf("token-> %s\n",token);
            token=strtok(NULL,sep);
            j++;
        }
        features[i].id=i;
        features[i].feature=mstring[i];
        token=NULL;
        }
    
    fclose(file);
    //return mstring;
    return features;
}