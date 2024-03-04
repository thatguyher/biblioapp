#include <iostream>
#include <utility>
#include "Etudiant.h"
#include "Livre.h"

Etudiant::Etudiant()
        : numeroMatricule(""), classe(""), filiere("") {
}

Etudiant::Etudiant(std::string nom, std::string prenom, std::string dateNaissance,
                   std::string numeroTelephone, std::string adresseResidence,
                   Personne *personneAPrevenirEnCasDeBesoin,
                   std::string numeroMatricule, std::string classe, std::string filiere)
        : Personne(std::move(nom),
                   std::move(prenom),
                   std::move(dateNaissance),
                   std::move(numeroTelephone),
                   std::move(adresseResidence),
                   personneAPrevenirEnCasDeBesoin),
          numeroMatricule(std::move(numeroMatricule)), classe(std::move(classe)), filiere(std::move(filiere)) {
}

// Constructeur de copie
Etudiant::Etudiant(const Etudiant &autre)
        : Personne(autre),
          numeroMatricule(autre.numeroMatricule),
          classe(autre.classe),
          filiere(autre.filiere),
          livresEmpruntes(autre.livresEmpruntes) {
}

void Etudiant::afficher() const {
    std::cout << "\n|=== ETUDIANT" << "\n";
    std::cout << "|-> ID: " << "ETD46479778" << "\n";
    std::cout << "|" << "\n";
    std::cout << "|=== Informations personnelles ===|" << "\n";
    std::cout << "|-> Nom: " << nom << "\n";
    std::cout << "|-> Prenom: " << prenom << "\n";
    std::cout << "|-> Date de naissance: " << dateNaissance << "\n";
    std::cout << "|-> Numero de telephone: " << numeroTelephone << "\n";
    std::cout << "|-> Adresse de residence: " << adresseResidence << "\n";
    std::cout << "|" << "\n";
    std::cout << "|=== Informations d'etudiant ===|" << "\n";
    std::cout << "|-> Numero matricule: " << numeroMatricule << "\n";
    std::cout << "|-> Classe: " << classe << "\n";
    std::cout << "|-> Filiere: " << filiere << "\n";
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

std::ostream &operator<<(std::ostream &os, const Etudiant &etudiant) {
    etudiant.afficher();
    return os;
}

int Etudiant::emprunterLivre(Livre& livre, std::string dateRetour) {
    return livre.emprunter(std::move(dateRetour));
}