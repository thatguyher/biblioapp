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

    // Getters
    std::string getAuteur() const;
    std::string getTitre() const;
    bool isDisponible() const;
    std::string getEtat() const;
    std::string getDateCreation() const;
    std::string getDateDernierEmprunt() const;
    std::string getDateRetour() const;

    // Setters
    void setAuteur(const std::string& auteur);
    void setTitre(const std::string& titre);
    void setDisponible(bool disponible);
    void setEtat(const std::string& etat);
    void setDateCreation(const std::string& dateCreation);
    void setDateDernierEmprunt(const std::string& dateDernierEmprunt);
    void setDateRetour(const std::string& dateRetour);

    const std::string &getIdEmprunt() const;

    void setIdEmprunt(const std::string &idEmprunt);

    const std::string &getId() const;

    void setId(const std::string &id);

//    Surcharge des operateurs
    // L'pérateurs <<
    friend std::ostream &operator<<(std::ostream &os, const Livre &livre);

    void afficher() const;

    // Actions metier
    int emprunter(std::string emprundId, std::string dateRetour);
    int retourner();


private:
    std::string auteur;
    std::string titre;
    bool disponible;
    std::string etat;
    std::string dateCreation;
    std::string dateDernierEmprunt;
    std::string dateRetour;
    std::string IdEmprunt;
    std::string id;
};

#endif //BIBLIOAPP_LIVRE_H