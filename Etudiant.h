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

    static void loadLastEtudiantNr();
    static void saveLastEtudiantNr();
    static int lastEtudiantNr;

    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Etudiant& etudiant);

    void afficher() const;

    const std::string &getNumeroMatricule() const;

    void setNumeroMatricule(const std::string &numeroMatricule);

    const std::string &getClasse() const;

    void setClasse(const std::string &classe);

    const std::string &getFiliere() const;

    void setFiliere(const std::string &filiere);

    const std::string &getId() const;

    void setId(const std::string &id);


private:
    std::string numeroMatricule;
    std::string classe;
    std::string filiere;
    std::string id;
};

#endif //BIBLIOAPP_ETUDIANT_H