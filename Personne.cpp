
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

// Constructeur de déplacement
Personne::Personne(Personne&& autre) noexcept
        : nom(std::move(autre.nom)), prenom(std::move(autre.prenom)), dateNaissance(std::move(autre.dateNaissance)),
          numeroTelephone(std::move(autre.numeroTelephone)), adresseResidence(std::move(autre.adresseResidence)),
          personneAPrevenirEnCasDeBesoin(autre.personneAPrevenirEnCasDeBesoin) {
    autre.personneAPrevenirEnCasDeBesoin = nullptr; // L'autre objet n'a plus de personne à prévenir
    // Implémentation du constructeur de déplacement
}

Personne::~Personne() {
    // Destructeur
}

[[noreturn]] void Personne::afficher() const {
    std::cout << "|=== PERSONNE ===================================" << "\n";
    std::cout << "|-> Nom: " << nom << "\n";
    std::cout << "|-> Prénom: " << prenom << "\n";
    std::cout << "|-> Date de naissance: " << dateNaissance << "\n";
    std::cout << "|-> Numéro de téléphone: " << numeroTelephone << "\n";
    std::cout << "|-> Adresse de résidence: " << adresseResidence << "\n";
    std::cout << "|=================================================" << "\n";

    if (personneAPrevenirEnCasDeBesoin != nullptr) {
        std::cout << "Personne à prévenir en cas de besoin:\n";
        personneAPrevenirEnCasDeBesoin->afficher();
    }
}