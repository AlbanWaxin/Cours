Exercice 5
On effectue un remplacement de toutes les valeurs du nouveaux buffer, pour s'assurer qu'il y a bien un marqueur de find de chaine et pour un soucis de sécurité mémoire

Exercice 6
La fonction free libère l'espace défini par un pointeur,c'est à dire qu'il met le pointeur à NULL sans modifier les données, il redeplace le heap de la pile mémoire.
La mémoire n'est pas vraiment libérée.

Exercice 17
Le buffer peut encore contenir des caractères à la fin de l'execution de la fonction mini_printf s'il n'était pas plein, il faut donc le print et effectivement retourner a la ligne pour pas que les prochaines commande se fassent sur la meme ligne que notre print

Exercice 22
le problème de ces fonctions c'est qu'elles ne vérifie pas la présence d'un terme de fin de chaine et de la taille, il y a donc des risques d'overflow

pour corriger on peut ajouter un parametre nombre de parametre pour etre sur que la cible peut acceuillir la source ainsi que le terme de fin

Exercice 34
Si l'on termine sans flush, une partie du texte ne sera pas afficher.



Annotation code:

pour compiler les executables de la question 39,40 et 41 le makefile a disposition est fonctionnel, entrer:

make 			Compile le main
make touch		Compile mini_touch
make cp			Compile mini_cp
make echo		Compile mini_echo
make cat		Compile mini_cat
make head		Compile mini_head
make tail		Compile mini_tail
make clean		Compile mini_claen
make grep		Compile mini_grep
make wc			Compile wc
make mini_shell		Compile mini_shell
make cleano		supprime les fichier .o
make cleanprog		supprime les executables


A noter pour tester le grep mettre au moins deux ligne (meme une 2eme ligne vide suffit)
Seules head et tail et cp ne sont pas appelables dans le mini_shell pour probleme de gestion d'argument

au moment du dépot les fonctions compilent toutes sans erreur ou warning.
