## Ceci est un mini programme de gestion de bibliothèque sous la forme d'un interprêteur de commandes.

### Guide d'utilisation

- documentation ou doc ou aide: Afficher la documentation.


- creer-livre -t TITRE -a AUTEUR : Cree un nouveau livre dans la bibliotheque.
-t TITRE : Titre du livre.
-a AUTEUR : Auteur du livre.


- modifier-livre -i IDENTIFIANT [-t TITRE] [-a AUTEUR] : Modifie les informations d'un livre existant.
-i IDENTIFIANT : Identifiant du livre a modifier.
-t TITRE (optionnel) : Nouveau titre pour le livre.
-a AUTEUR (optionnel) : Nouvel auteur pour le livre.


- supprimer-livre -i IDENTIFIANT : Supprime un livre specifique de la bibliotheque et lister les identifiants des emprunts supprimes.
-i IDENTIFIANT : Identifiant du livre a supprimer.


- lister-livres [-d oui/non] : Liste tous les livres dans la bibliotheque.
-d oui/non (optionnel) : Liste les livres en fonction de leur disponibilite. "oui" pour les livres disponibles, "non" pour les livres empruntes.


- details-livre -i IDENTIFIANT : Affiche en detail les informations d'un livre specifique.
-i IDENTIFIANT : Identifiant du livre.


- lister-emprunteurs -i IDENTIFIANT : Liste tous les étudiants qui ont emprunte un livre specifique.
-i IDENTIFIANT : Identifiant du livre.


- creer-etudiant -n NOM -p PRENOM -dn DATE_NAISSANCE -t TELEPHONE -addr ADRESSE -m MATRICULE -c CLASSE -f FILIERE : Creer un nouvel etudiant.
-n NOM : Nom de l'etudiant.
-p PRENOM : Prénom de l'etudiant.
-dn DATE_NAISSANCE : Date de naissance de l'etudiant.
-t TELEPHONE : Numero de telephone de l'etudiant.
-addr ADRESSE : Adresse residentielle de l'etudiant.
-m MATRICULE : Numero de matricule de l'etudiant.
-c CLASSE : Classe de l'etudiant.
-f FILIERE : Filiere de l'etudiant.


- modifier-etudiant -i IDENTIFIANT [...] : Modifie les informations d'un etudiant existant. Les informations pour la modification
suivent le meme format que pour creer-etudiant (a l'exception de -i IDENTIFIANT).


- supprimer-etudiant -i IDENTIFIANT : Supprime un etudiant specifique et liste les identifiants des emprunts supprimes.
-i IDENTIFIANT : Identifiant de l'etudiant.


- lister-emprunts -i IDENTIFIANT : Liste tous les livres empruntes par un etudiant specifique.
-i IDENTIFIANT : Identifiant de l'etudiant.


- details-etudiant -i IDENTIFIANT : Affiche en detail les informations d'un etudiant specifique.
-i IDENTIFIANT : Identifiant de l'etudiant.


- lister-etudiants : Liste tous les etudiants.


- preter -l IDENTIFIANT_LIVRE -e IDENTIFIANT_ETUDIANT -dr DATE_RETOUR : Emprunte un livre specifique a un etudiant specifique.
-l IDENTIFIANT_LIVRE : Identifiant du livre.
-e IDENTIFIANT_ETUDIANT : Identifiant de l'etudiant.
-dr DATE_RETOUR : Date de retour prevue pour l'emprunt.


- recuperer -l IDENTIFIANT_LIVRE -e IDENTIFIANT_ETUDIANT : Declare qu'un livre specifique a ete retourne par un etudiant specifique.
-l IDENTIFIANT_LIVRE : Identifiant du livre.
-e IDENTIFIANT_ETUDIANT : Identifiant de l'etudiant.


- sauvegarder : Sauvegarde l'etat actuel de la bibliotheque (livres, etudiants, emprunts).


- quitter ou q : Sauvegarde et quitte l'application.
