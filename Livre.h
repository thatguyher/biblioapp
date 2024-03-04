#ifndef BIBLIOAPP_LIVRE_H
#define BIBLIOAPP_LIVRE_H

#include <iostream>
#include <string>
#include <vector>

extern const std::string ETAT_EXPLOITABLE;
extern const std::string ETAT_NON_EXPLOITABLE;

class Livre {
public:
//    Constructeurs
    Livre();
    Livre(std::string auteur, std::string titre);
    // Constructeur de copie
    Livre(const Livre &autre);

//    Surcharge des operateurs
    // L'pérateurs <<
    friend std::ostream &operator<<(std::ostream &os, const Livre &livre);

    void afficher() const;

    // Actions metier
    int emprunter(std::string dateRetour);
    int retourner();

private:
    std::string auteur;
    std::string titre;
    bool disponible;
    std::string etat;
    std::string dateCreation;
    std::string dateDernierEmprunt;
    std::string dateRetour;
};

#endif //BIBLIOAPP_LIVRE_H