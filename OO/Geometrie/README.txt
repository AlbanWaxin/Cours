Exercice 1:

b) Lors de l'instanciation du rectangle il appel le constructeur Rectangle qui appel le constructeur de quadrilateral qui appel celui de GeometricalShape
puis les draw sont directement hérité de GeometricalShape
de meme pour les draws point et sans argument


c) le polymorphisme est implicite , il s'agit d'une liaison tardive et on execute la methode la plus proche parmis les constructeur hérités


d) on a bien le type le plus proche il s'agit donc de liaison tardive  

e) La liaison tardive faite au moment de l’exécution. Cette liaison s’intéresse aux
types réels et s’applique typiquement au cas de redéfinition en java.

f) il s'agit d'un transtypage ascendant, et il est légitime car la relation d'héritage sous entend l'existence d'une relation de sous-type

g) le message dis que l'on ne peut pas caster un type parent sur son type enfant, il faut vérifier qu'ils sont compatibles.

h) la liste étant une liste de geometricalshape, a la compilation il regarde le type reel du tableau qui n'a pas de getPerimeter() et donc
