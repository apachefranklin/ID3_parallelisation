Ici la description de l'algorithme inbuilMemomery Node

    il prend entre un dataset et un ensemble de colone a ignorer
    Pour chaque colone on verfie si elle ne fait pas partie des colones a ignorer
        Ensuite on calcule le **gain d'information** pour chaqu'une des colones.
        La colone qui a le gain maximale est le nom de notre noeud
        Nous creeons donc des datasets base sur chaqu'une des valeurs
        Nous creeons egalement des branches baser sur chaqu'une valeur
        Nous creeons egalemet des fils. 

        Maintenant pour chaqu'une des valeurs de cette colone on verifie si elle possede plus de deux classes associer  on construt l'arbre sur un noeud creer pour l'ocasion
        Sinon on considere cela comme une prediction