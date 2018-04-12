# ft_ls
Le projet ft_ls et le premier projet de la branche système du cursus de l'ecole 42.
Ce projet conciste a recoder la commande 'ls' d'un système UNIX (Mac OS X dans mon cas) avec les options suivantes:
-R -S -U -a -c -d -l -r -t -u -1 ayant les mêmes caracteristique que ces mêmes options avec la commande 'ls' de Mac OS X Sierra

Usage: ./ft_ls [-RSUacdlrtu1] [file ...]

# Compilation (gcc ou clang)
Executez la ligne de commande suivant pour recuperer les dependances necessaire a la compilation:

    git submodule init && git submodule update
Puis, pour compiler le projet lancez simplement la commande:

    make
l'executable sera créé a la racine du projet.

# Exemples d'utilisation
    ./ft_ls -Rla /dev
ou

    ./ft_ls -R -l -a /dev
Affichera les informations detaillées (option -l) concernant chaques fichiers (cachés ou non, option -a) contenu dans le repertoire '/dev' ainsi que tout ceux contenus dans les sous-repertoires de '/dev' (option -R) avec un fichier par ligne.
