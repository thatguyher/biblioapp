#ifndef BIBLIOAPP_ETUDIANT_H
#define BIBLIOAPP_ETUDIANT_H

#include "Personne.h"
#include "Livre.h"
#include <vector>

class Etudiant : public Personne {
public:
    Etudiant();
    Etudiant(std::string nom, std::string prenom, std::string dateNaissance,
             std::string numeroTelephone, std::string adresseResidence,
             Personne* personneAPrevenirEnCasDeBesoin,
             std::string numeroMatricule, std::string classe, std::string filiere);

    // Constructeur de copie
    Etudiant(const Etudiant& autre);

    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Etudiant& etudiant);

    void afficher() const;

    // Méthode pour emprunter un livre
    int emprunterLivre(Livre& livre, std::string dateRetour);

private:
    std::string numeroMatricule;
    std::string classe;
    std::string filiere;
    std::vector<Livre> livresEmpruntes;
};

#endif //BIBLIOAPP_ETUDIANT_H