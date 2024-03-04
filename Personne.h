//
// Created by BRAD on 04/03/2024.
//

#ifndef BIBLIOAPP_PERSONNE_H
#define BIBLIOAPP_PERSONNE_H


#include <string>

class Personne {
public:
    Personne();
    Personne(std::string  nom, std::string  prenom, std::string  dateNaissance,
             std::string  numeroTelephone, std::string  adresseResidence,
             Personne* personneAPrevenirEnCasDeBesoin);
    // Constructeur de copie
    Personne(const Personne& autre);
    // Constructeur de déplacement
    Personne(Personne&& autre) noexcept;

    ~Personne();

    // Fonction amie pour surcharger l'opérateur de sortie
    friend std::ostream& operator<<(std::ostream& os, const Personne& personne);

    [[noreturn]] void afficher(bool i = false) const;

private:
    std::string nom;
    std::string prenom;
    std::string dateNaissance;
    std::string numeroTelephone;
    std::string adresseResidence;
    Personne* personneAPrevenirEnCasDeBesoin;

};


#endif //BIBLIOAPP_PERSONNE_H
