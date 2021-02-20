#include <stdlib.h>
#include <stdio.h>
#include "Header/function.h"

int direBonjour(char name[]){
    printf("Bonjour %s",name);
    return 0;
}
int main(int argc, char *argv[]){
    direBonjour(",apache est tres en fait\n");

    double votrepoids=0;
    printf("votre poids est de %f , mais bon!!!\n\n",votrepoids);
    printf("Veuillez entrez votre nouveau poids\n\n");
    scanf("%lf",&votrepoids);
    printf("votre nouveau poids est de %f , mais bon!!!\n\n",votrepoids);

    printf("Bonjour apache!!!! tu es de retour en C\n \n");

    printf("Maintenant nous devons tester les operations raccoucis\n\n");

    int a=78;
    ++a;
    printf("On teste la nouvelle valeur de a qui est %d \n \n \n \n \n",a);

    printf("Test des conditions booelennennes sur les entiers\n\n");
    if (!0){
        printf("On exceute");
    }
    else {
        printf("On execute pas");
    }
    //replace(&votrepoids,&a);

    char *nom=NULL;

    printf("Veuillez entrer votre nom\n  ->");
    scanf("%s",nom);
    printf("Le nom que vous venez d'entrez est %s",*nom);
    return 89;
}