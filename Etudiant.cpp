#include <iostream>
#include <utility>
#include "Etudiant.h"
#include "Livre.h"

#include <fstream>

const std::string FILE_LAST_ETUDIANT_NR = "lastEtudiantNr.txt";
const std::string FILE_ETUDIANTS = "etudiants_file.danyl";
int Etudiant::lastEtudiantNr = 0;

Etudiant::Etudiant()
        :
        id(""),
        numeroMatricule(""),
        classe(""),
        filiere("") {}

Etudiant::Etudiant(std::string id, std::string nom, std::string prenom, std::string dateNaissance,
                   std::string numeroTelephone, std::string adresseResidence,
                   Personne *personneAPrevenirEnCasDeBesoin,
                   std::string numeroMatricule, std::string classe, std::string filiere)
        : id(std::move(id)),
          Personne(std::move(nom),
                   std::move(prenom),
                   std::move(dateNaissance),
                   std::move(numeroTelephone),
                   std::move(adresseResidence),
                   personneAPrevenirEnCasDeBesoin),
          numeroMatricule(std::move(numeroMatricule)),
          classe(std::move(classe)),
          filiere(std::move(filiere)) {}

// Constructeur de copie
Etudiant::Etudiant(const Etudiant &autre)
        : Personne(autre),
          id(autre.id),
          numeroMatricule(autre.numeroMatricule),
          classe(autre.classe),
          filiere(autre.filiere) {}

std::string Etudiant::generateEtudiantId() {
    loadLastEtudiantNr();
    lastEtudiantNr++;
    char empruntNr[5];
    sprintf(empruntNr, "%04d", lastEtudiantNr);

    std::string id = "ETD" + std::string(empruntNr);
    saveLastEtudiantNr();

    return id;
}

void Etudiant::afficher() const {
    std::cout << "\n|=== ETUDIANT" << "\n";
    std::cout << "|-> ID: " << id << "\n";
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

const std::string &Etudiant::getNumeroMatricule() const {
    return numeroMatricule;
}

void Etudiant::setNumeroMatricule(const std::string &numeroMatricule) {
    Etudiant::numeroMatricule = numeroMatricule;
}

const std::string &Etudiant::getClasse() const {
    return classe;
}

void Etudiant::setClasse(const std::string &classe) {
    Etudiant::classe = classe;
}

const std::string &Etudiant::getFiliere() const {
    return filiere;
}

void Etudiant::setFiliere(const std::string &filiere) {
    Etudiant::filiere = filiere;
}

const std::string &Etudiant::getId() const {
    return id;
}

void Etudiant::loadLastEtudiantNr() {
    std::ifstream infile(FILE_LAST_ETUDIANT_NR);
    if (infile.good()) {
        infile >> lastEtudiantNr;
    }
    infile.close();
}

void Etudiant::saveLastEtudiantNr() {
    std::ofstream outfile(FILE_LAST_ETUDIANT_NR);
    if (outfile.good()) {
        outfile << lastEtudiantNr;
    }
    outfile.close();
}

int Etudiant::save(const Etudiant &etd) {
    std::ofstream outFile(FILE_ETUDIANTS, std::ios::app); // open file in append mode

    if (outFile.is_open()) {
        outFile << etd.getId() << "\n"
                << etd.getNom() << "\n"
                << etd.getPrenom() << "\n"
                << etd.getDateNaissance() << "\n"
                << etd.getNumeroTelephone() << "\n"
                << etd.getAdresseResidence() << "\n"
                << etd.getNumeroMatricule() << "\n"
                << etd.getClasse() << "\n"
                << etd.getFiliere() << "\n"
                << "-----" << "\n";   // Add a separator between instances for readability
        outFile.close();
        return 0;
    } else {
        return 1;
    }
}

void Etudiant::saveMultiple(const std::vector<Etudiant> *etudiants) {
    // Open the file in overwrite mode.
    // Any previous content will be deleted.
    std::ofstream outFile(FILE_ETUDIANTS);
    outFile.close();

    for (const Etudiant &etd: *etudiants) {
        save(etd);
    }
}

std::vector<Etudiant> Etudiant::loadMultiple() {
    std::vector<Etudiant> etudiants;
    std::ifstream inFile(FILE_ETUDIANTS);
    std::string line;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            Etudiant etd;
            if (!line.empty()) etd.setId(line);
            if (std::getline(inFile, line)) etd.setNom(line);
            if (std::getline(inFile, line)) etd.setPrenom(line);
            if (std::getline(inFile, line)) etd.setDateNaissance(line);
            if (std::getline(inFile, line)) etd.setNumeroTelephone(line);
            if (std::getline(inFile, line)) etd.setAdresseResidence(line);
            if (std::getline(inFile, line)) etd.setNumeroMatricule(line);
            if (std::getline(inFile, line)) etd.setClasse(line);
            if (std::getline(inFile, line)) etd.setFiliere(line);
            etudiants.push_back(etd);
            std::getline(inFile, line); // read the "-----" line (delimiter)
        }
        inFile.close();
    } else {
        // Handle error - cannot open file for reading
    }

    return etudiants;
}

void Etudiant::setId(const std::string &newId) {
    id = newId;
}
