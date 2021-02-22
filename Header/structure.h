#include <stdlib.h>
#include <stdio.h>
#define STRUCTURE_H_INCLUDED

/**
 * Ceci repersente une abstraction d'une chaine de caractere
 * value represente sa valeur
*/
typedef struct MyString MyString;
struct MyString{
    char value[100];
};


/**
 * Structure definissant une ligne de notre jeu de donnees
 * on peut avoir nom prenom age 
 * representer par 1 nom prenom age 
**/
typedef struct FeatureLine FeatureLine;
struct FeatureLine{
    MyString *feature;
    int id;
};


/**
 * Cette struture represente la branche d'un arbre
 * Ici nous devons connaitre le contenu d'une branche
*/
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

/**
 * Cette structure represente un noeud
 * de l'arbre de decision
*/
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

/**
 * cette structure represente l'arbre
 * de decision qui sera construit du noeud racine
*/
typedef struct Tree Tree;
struct Tree{
    Noeud racine;
};
