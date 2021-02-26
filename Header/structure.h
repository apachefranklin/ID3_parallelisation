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
typedef struct Feature Feature;
struct Feature{
    MyString *feature;
    int id;
};

/**
 * Cette structure permet de representer
 * soit tout soit une partir de notre 
 * jeu de donnée
 * @property Feature *features
 * @property MyString *colnames
 * @property Mystring *targets
 * @property int rows
 * @property int nbcols
 * @param param features,colnames,targets,rows,cols;
*/
typedef struct Dataset Dataset;
struct Dataset
{
    Feature *features;
    MyString *colnames;
    MyString *targets;
    int rows;
    int cols;
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
typedef struct Node Node;
struct Node
{
    char name[100];
    int prediction; 
    //cette valeur a -1 signifie que nous avons encore des datas restant a predire
    Branche *branches; 
    //represente les branches possibles
    Node *fils;
};

/**
 * cette structure represente l'arbre
 * de decision qui sera construit du noeud racine
*/
typedef struct Tree Tree;
struct Tree{
    Node root;
};
