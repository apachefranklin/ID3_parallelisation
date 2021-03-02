#define STRUCTURE_H_INCLUDED
#define OUT_OF_MEMORY_LENGTH 50

/**
 * Ceci repersente une abstraction d'une chaine de caractere
 * value represente sa valeur
*/
typedef struct MyString MyString;
struct MyString
{
    char value[100];
};

/**
 * Structure definissant une ligne de notre jeu de donnees
 * on peut avoir nom prenom age 
 * representer par 1 nom prenom age 
**/
typedef struct Vector Vector;
struct Vector
{
    MyString *values;
    int length;
};

/**
 * Structure definissant une ligne de notre jeu de donnees
 * on peut avoir nom prenom age 
 * representer par 1 nom prenom age 
**/
typedef struct Feature Feature;
struct Feature
{
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
    int real_size; //le dataset peut etre un sous dataset, dans ce cas real_size represente la taille relle de ce dataset
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
    int length; //represente le nombre de branches ainsi que de fils
    //cette valeur a -1 signifie que nous avons encore des datas restant a predire
    MyString *branches;
    //represente les branches possibles
    Node *fils;
};

/**
 * cette structure represente l'arbre
 * de decision qui sera construit du noeud racine
*/

typedef struct Tree Tree;
struct Tree
{
    Node root;
};

typedef struct Model Model;
struct Model
{
    Node root_node;
    int n_attributes;
    MyString *attributes;
    double score;
};

//////*STRUCTURE POUR MAP REDUCE*//////

/*
*usage: MapOuput* contains list of key value pair
*key is the attribute name
*value is the gain computed by the mapper.
* 
*/
typedef struct MapOutput
{
    MyString key;
    double value;
} MapOutput;

/*
*encapsulates input arguments of a mapper
*/
typedef struct MapperArg
{
    int id_map;
    Dataset *dataset;
    int *cols; // col indexes to be considered
    double weigth; //represente le poids qu'on va multiplier les entropys et les gains d'information avec
    int ncol;  //lengh of col indexes
    int *rows; //
    int nrow;
    MapOutput *output; // set of key value pair to compute
    int npair;         //number of key value paris
} MapperArg;

/*
*Usage: ShufleOutput* a list of grouped key-value  pairs
*key is a colname attribute
*values is the list of gains computed by each mapper.
*/
typedef struct ShufleOutput
{
    MyString key;
    double *values;
    int length;
} ShufleOutput;

/*
* arguments for the shufle function
*/
typedef struct ShufleArg
{
    MapperArg *m_args; //mappers argument, whith field
    int length_m_args;

    MapOutput *m_outputs; //set of intermediate key values computed by Map
    int length_m_outputs;

    ShufleOutput *outputs; // list grouped by key key value to compute
    int length_output;

} ShufleArg;

/*
* when a reducer ends it job, it modifies, ReducerArg.key
* and ReducerArg.gain. 
* so &ReducerArg must be taken as reducer parameter.
*/
typedef struct ReducerArg
{
    int id_reducer;
    ShufleOutput *inputs; // the shufle output list
    int length_inputs;
    MyString key; //output: the col name attribute that maximize the gain
    double gain;  //output: the max gain.

} ReducerArg;
