# ft_ls
Le projet ft_ls et le premier projet de la branche système du cursus de l'école 42.
Ce projet consiste a recoder la commande 'ls' d'un système UNIX (Mac OS X dans mon cas) avec les options suivantes:
-R -S -U -a -c -d -l -r -t -u -1 ayant les mêmes caractéristique que ces mêmes options avec la commande 'ls' de Mac OS X Sierra

Usage: ./ft_ls [-RSUacdlrtu1] [file ...]

# Compilation (gcc ou clang)
(Attention: ce projet à été réalisé pour Mac OS X Sierra, il pourrait y avoir des erreurs de compilation sur d'autre systèmes) 
Exécutez la ligne de commande suivant pour récupérer les dépendances nécessaire a la compilation:

    git submodule init && git submodule update
Puis, pour compiler le projet lancez simplement la commande:

    make
l'exécutable sera créé a la racine du projet.

# Exemples d'utilisation
    ./ft_ls -Rla /dev
ou

    ./ft_ls -R -l -a /dev
Affichera les informations détaillées (option -l) concernant chaque fichiers (cachés ou non, option -a) contenu dans le répertoire '/dev' ainsi que tout ceux contenus dans les sous-répertoires de '/dev' (option -R) avec un fichier par ligne.
