Réponse questions:

Question 10) le echo ne renvoi rien, on a besoin d'un client qui va renboyer le messae lui aussi

Server IRC:

les noms des fonctions ne sont pas censible à la casse.
Les fonctions suivantes fonctionnent comme demandé:
    -nickname  ferme la socket si on se connecte avec mot de passe a un pseudo déjà utilisé
    -register (les mots de passent sont stockés en clair dans un txt du dossier)
    -unregister 
    -exit 
    -date et le date client utilisent l'heure système du a un problème avec la requete ntp
    -mp 
    -alerte ecrit en rouge et gras
    -alerte pseudo
    -send fonctionne, stock dans un fichier a part, mais est fragile si les prints de fin apparaissent pas ,envoyer un message peu finir le problème
    -couleurs

Spécificités:

    make disponible : make server pour generer le server
                      make client pour generer le client

    ./client 8000 127.0.0.1 a été utilisé pour les test.

    Pas de problème apparent lors des test,