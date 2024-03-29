
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

    // Fonction amie pour surcharger l'opérateur de sortie
    friend std::ostream& operator<<(std::ostream& os, const Personne& personne);

    // Getters
    // Declare the getters
    std::string getNom() const;
    std::string getPrenom() const;
    std::string getDateNaissance() const;
    std::string getNumeroTelephone() const;
    std::string getAdresseResidence() const;
    Personne* getPersonneAPrevenirEnCasDeBesoin() const;

    void setNom(const std::string &nom);

    void setPrenom(const std::string &prenom);

    void setDateNaissance(const std::string &dateNaissance);

    void setNumeroTelephone(const std::string &numeroTelephone);

    void setAdresseResidence(const std::string &adresseResidence);

    void setPersonneAPrevenirEnCasDeBesoin(Personne *personneAPrevenirEnCasDeBesoin);

    void afficher() const;

protected:
    std::string nom;
    std::string prenom;
    std::string dateNaissance;
    std::string numeroTelephone;
    std::string adresseResidence;
    Personne* personneAPrevenirEnCasDeBesoin;

};


#endif //BIBLIOAPP_PERSONNE_H
