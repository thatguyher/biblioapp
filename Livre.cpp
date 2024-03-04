#include "Livre.h"

#include <utility>
#include "utils.h"

const std::string ETAT_EXPLOITABLE = "Exploitable";
const std::string ETAT_NON_EXPLOITABLE = "Non exploitable";

// Constructeur par défaut
Livre::Livre() : disponible(true),
                 etat(ETAT_NON_EXPLOITABLE),
                 dateCreation(getCurrentDate()) {}

// Constructeur avec paramètres
Livre::Livre(std::string auteur, std::string titre)
        : auteur(std::move(auteur)),
          titre(std::move(titre)),
          disponible(true),
          etat(ETAT_EXPLOITABLE),
          dateCreation(getCurrentDate()) {}

// Constructeur de copie
Livre::Livre(const Livre &autre)
        : auteur(autre.auteur),
          titre(autre.titre),
          disponible(autre.disponible),
          etat(autre.etat),
          dateCreation(autre.dateCreation),
          dateDernierEmprunt(autre.dateDernierEmprunt),
          dateRetour(autre.dateRetour) {}

void Livre::afficher() const {
    std::cout << "\n|=== LIVRE" << "\n";
    std::cout << "|-> ID: " << "LVR46479778" << "\n";
    std::cout << "|" << "\n";
    std::cout << "|-> Auteur: " << auteur << "\n";
    std::cout << "|-> Titre: " << titre << "\n";
    std::cout << "|-> Disponible ?: " << (disponible ? "Oui" : "Non") << "\n";
    std::cout << "|-> Etat: " << etat << "\n";
    std::cout << "|-> Date de creation: " << dateCreation << "\n";
    std::cout << "|-> Date du dernier emprunt: " << dateDernierEmprunt << "\n";
    std::cout << "|-> Date de retour prevue: " << dateRetour << "\n";
    std::cout << "|===\n";
}

std::ostream &operator<<(std::ostream &os, const Livre &livre) {
    livre.afficher();
    return os;
}

int Livre::emprunter(std::string retourDate) {
    if (disponible && etat == ETAT_EXPLOITABLE) {
        disponible = false;
        dateDernierEmprunt = getCurrentDate();
        dateRetour = std::move(retourDate);
        //TODO: Creer une instance d'emprunt et mettre l'état à 1
        return 0;
    } else if (!disponible) {
        return 1;
    } else {
        return 2;
    }
}

int Livre::retourner() {
    if (!disponible) {
        disponible = true;
        dateRetour = getCurrentDate();
        //TODO: Mettre l'etat de l'emprunt à 0
        return 0;
    } else {
        return 1;
    }
}