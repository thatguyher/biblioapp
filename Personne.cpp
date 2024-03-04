
#include "Personne.h"

#include <utility>
#include <iostream>

Personne::Personne() : personneAPrevenirEnCasDeBesoin(nullptr) {
    // Constructeur par défaut
}

Personne::Personne(std::string  nom, std::string  prenom, std::string  dateNaissance,
                   std::string  numeroTelephone, std::string  adresseResidence,
                   Personne* personneAPrevenirEnCasDeBesoin)
        : nom(std::move(nom)), prenom(std::move(prenom)), dateNaissance(std::move(dateNaissance)),
          numeroTelephone(std::move(numeroTelephone)), adresseResidence(std::move(adresseResidence)),
          personneAPrevenirEnCasDeBesoin(personneAPrevenirEnCasDeBesoin) {
    // Constructeur avec paramètres
}

// Constructeur de copie
Personne::Personne(const Personne& autre)
        : nom(autre.nom), prenom(autre.prenom), dateNaissance(autre.dateNaissance),
          numeroTelephone(autre.numeroTelephone), adresseResidence(autre.adresseResidence),
          personneAPrevenirEnCasDeBesoin(autre.personneAPrevenirEnCasDeBesoin) {
    // Implémentation du constructeur de copie
}


// Getters
std::string Personne::getNom() const {
    return nom;
}

std::string Personne::getPrenom() const {
    return prenom;
}

std::string Personne::getDateNaissance() const {
    return dateNaissance;
}

std::string Personne::getNumeroTelephone() const {
    return numeroTelephone;
}

std::string Personne::getAdresseResidence() const {
    return adresseResidence;
}

Personne* Personne::getPersonneAPrevenirEnCasDeBesoin() const {
    return personneAPrevenirEnCasDeBesoin;
}

// Metier
void Personne::afficher() const {
    std::cout << "\n|=== PERSONNE" << "\n";
    std::cout << "|-> ID: " << "PER46479778" << "\n";
    std::cout << "|" << "\n";
    std::cout << "|-> Nom: " << nom << "\n";
    std::cout << "|-> Prenom: " << prenom << "\n";
    std::cout << "|-> Date de naissance: " << dateNaissance << "\n";
    std::cout << "|-> Numero de telephone: " << numeroTelephone << "\n";
    std::cout << "|-> Adresse de residence: " << adresseResidence << "\n";
    if (personneAPrevenirEnCasDeBesoin != nullptr) {
        std::cout << "|" << "\n";
        std::cout << "|=== Personne a prevenir en cas de besoin ===|\n";
        std::cout << "|-> Nom: " << personneAPrevenirEnCasDeBesoin->getNom() << "\n";
        std::cout << "|-> Prenom: " << personneAPrevenirEnCasDeBesoin->getPrenom() << "\n";
        std::cout << "|-> Date de naissance: " << personneAPrevenirEnCasDeBesoin->getDateNaissance() << "\n";
        std::cout << "|-> Numero de telephone: " << personneAPrevenirEnCasDeBesoin->getNumeroTelephone() << "\n";
        std::cout << "|-> Adresse de residence: " << personneAPrevenirEnCasDeBesoin->getAdresseResidence() << "\n";
    }
    std::cout << "|===\n";
}

std::ostream& operator<<(std::ostream& os, const Personne& personne) {
    personne.afficher();
    return os;
}