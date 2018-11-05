# projetDemineurC
Projet licence ACSID
Programmation d'un démineur

Faire : " gcc -c *.c ; gcc -o prog *.o ; ./prog " pour lancer le code.

Menu au démarrage :

1) Nouvelle partie
2) Continuer derniere partie
3) Quitter

Le terrain est un Tableau de structure CaseTerrain
Une caseTerrain a 
- un état ( 0 la case est fermé , 1 la case est ouverte, 2 la case est flague )
- un contenu ( 0 la case est vide, 9 la case continent une bombe, ou le nombre de bombe dans les cases voisines )
- une positionX //que l'on a réussi a ne pas utiliser
- une positionY //que l'on a reussi a ne pas utiliser

L'utilisateur va rentrer les coordonees de la case qu'il souhaite ouvrir ou flager/deflager.

L'utilisateur ne peut pas fermer/flaguer une case ouverte.

A chaque fin de tour l'utilisateur pourra revenir en arriere, continuer ou quitter.

La partie se fini quand on ouvre toute les cases vides et toutes les bombes flaggé, ou quand on ouvre une bombe.
