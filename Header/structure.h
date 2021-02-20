#include <stdlib.h>
#include <stdio.h>
#define STRUCTURE_H_INCLUDED

typedef struct MyString MyString;
struct MyString{
    char value[100];
};

typedef struct Branche Branche;
struct Branche
{
    char name[100]; 
    /*
        name represente le nom de la branche c'est grace a lui, 
        qu'on saura la decision
        a prendre
        Il est en fait la valeur d'un attribut
    */
   int prediction; //cette variable est utiliser dans le cas ou nous avons a faire a une prediction
};

typedef struct Noeud Noeud;
struct Noeud
{
    char name[100];
    int prediction; 
    //cette valeur a -1 signifie que nous avons encore des datas restant a predire
    Branche *branches; 
    //represente les branches possibles
    Noeud *fils;
};

/*
    Noeud a son nom , sa potentiel predictions
    et ensuite ses potentiels fils
*/
