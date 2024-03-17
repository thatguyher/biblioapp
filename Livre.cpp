#include "Livre.h"

#include <utility>
#include "utils.h"

#include <fstream>

const std::string FILE_LAST_LIVRE_NR = "lastLivreNr.txt";
const std::string FILE_LIVRES = "livres_file.DAAJ"; // File to store Livre objects
int Livre::lastLivreNr = 0;


const std::string ETAT_EXPLOITABLE = "Exploitable";
const std::string ETAT_NON_EXPLOITABLE = "Non exploitable";

// Constructeur par défaut
Livre::Livre() : id(""),
                 disponible(true),
                 etat(ETAT_NON_EXPLOITABLE),
                 dateCreation(getCurrentDate()) {}

// Constructeur avec paramètres
Livre::Livre(std::string id, std::string auteur, std::string titre)
        : id(std::move(id)),
          auteur(std::move(auteur)),
          titre(std::move(titre)),
          disponible(true),
          etat(ETAT_EXPLOITABLE),
          dateCreation(getCurrentDate()) {}

// Constructeur de copie
Livre::Livre(const Livre &autre)
        : id(autre.id),
          auteur(autre.auteur),
          titre(autre.titre),
          disponible(autre.disponible),
          etat(autre.etat),
          dateCreation(autre.dateCreation),
          dateDernierEmprunt(autre.dateDernierEmprunt),
          dateRetour(autre.dateRetour) {}

// getters
std::string Livre::getAuteur() const {
    return auteur;
}

std::string Livre::getTitre() const {
    return titre;
}

bool Livre::isDisponible() const {
    return disponible;
}

std::string Livre::getEtat() const {
    return etat;
}

std::string Livre::getDateCreation() const {
    return dateCreation;
}

std::string Livre::getDateDernierEmprunt() const {
    return dateDernierEmprunt;
}

std::string Livre::getDateRetour() const {
    return dateRetour;
}

// Setters
void Livre::setAuteur(const std::string &aAuteur) {
    auteur = aAuteur;
}

void Livre::setTitre(const std::string &aTitre) {
    titre = aTitre;
}

void Livre::setDisponible(bool aDisponible) {
    disponible = aDisponible;
}

void Livre::setEtat(const std::string &aEtat) {
    etat = aEtat;
}

void Livre::setDateCreation(const std::string &aDateCreation) {
    dateCreation = aDateCreation;
}

void Livre::setDateDernierEmprunt(const std::string &aDateDernierEmprunt) {
    dateDernierEmprunt = aDateDernierEmprunt;
}

void Livre::setDateRetour(const std::string &aDateRetour) {
    dateRetour = aDateRetour;
}

std::string Livre::generateLivreId() {
    loadLastLivreNr();
    lastLivreNr++;

    char empruntNr[5];
    sprintf(empruntNr, "%04d", lastLivreNr);

    // Create ID in format "LVR" + 4 digit number
    std::string id = "LVR" + std::string(empruntNr);
    saveLastLivreNr();

    return id;
}

void Livre::afficher() const {
    std::cout << "\n|=== LIVRE" << "\n";
    std::cout << "|-> ID: " << id << "\n";
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

int Livre::emprunter(std::string emprundId, std::string retourDate) {
    if (disponible && etat == ETAT_EXPLOITABLE) {
        IdEmprunt = emprundId;
        disponible = false;
        dateDernierEmprunt = getCurrentDate();
        dateRetour = std::move(retourDate);
        return 0; // Ok
    } else if (!disponible) {
        return 1; // Non disponible
    } else {
        return 2; // Non exploitable
    }
}

int Livre::retourner() {
    if (!disponible) {
        disponible = true;
        dateRetour = getCurrentDate();
        return 0;
    } else {
        return 1;
    }
}

const std::string &Livre::getIdEmprunt() const {
    return IdEmprunt;
}

void Livre::setIdEmprunt(const std::string &idEmprunt) {
    IdEmprunt = idEmprunt;
}

const std::string &Livre::getId() const {
    return id;
}

void Livre::setId(const std::string &id) {
    Livre::id = id;
}

void Livre::loadLastLivreNr() {
    std::ifstream infile(FILE_LAST_LIVRE_NR);
    if (infile.good()) {
        infile >> lastLivreNr;
    }
    infile.close();
}

void Livre::saveLastLivreNr() {
    std::ofstream outfile(FILE_LAST_LIVRE_NR);
    if (outfile.good()) {
        outfile << lastLivreNr;
    }
    outfile.close();
}

int Livre::save(const Livre &livre) {
    std::ofstream outFile(FILE_LIVRES, std::ios::app); // open file in append mode

    if (outFile.is_open()) {
        outFile << livre.getId() << "\n"
                << livre.getAuteur() << "\n"
                << livre.getTitre() << "\n"
                << (livre.isDisponible() ? "True" : "False") << "\n"
                << livre.getEtat() << "\n"
                << livre.getDateCreation() << "\n"
                << livre.getDateDernierEmprunt() << "\n"
                << livre.getDateRetour() << "\n"
                << livre.getId() << "\n"
                << "-----" << "\n";  // Add a separator between instances for readability
        outFile.close();
        return 0;
    } else {
        return 1;
    }
}

void Livre::saveMultiple(const std::vector<Livre> *livres) {
    // Open the file in overwrite mode.
    // Any previous content will be deleted.
    std::ofstream outFile(FILE_LIVRES);
    outFile.close();

    for (const Livre &livre: *livres) {
        save(livre);
    }
}

std::vector<Livre> Livre::loadMultiple() {
    std::vector<Livre> livres;
    std::ifstream inFile(FILE_LIVRES);
    std::string line;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            Livre livre;
            if (!line.empty()) livre.setId(line);
            if (std::getline(inFile, line)) livre.setAuteur(line);
            if (std::getline(inFile, line)) livre.setTitre(line);
            if (std::getline(inFile, line)) livre.setDisponible(line == "True");
            if (std::getline(inFile, line)) livre.setEtat(line);
            if (std::getline(inFile, line)) livre.setDateCreation(line);
            if (std::getline(inFile, line)) livre.setDateDernierEmprunt(line);
            if (std::getline(inFile, line)) livre.setDateRetour(line);
            if (std::getline(inFile, line)) livre.setId(line);
            livres.push_back(livre);
            std::getline(inFile, line); // read the "-----" line (delimiter)
        }
        inFile.close();
    } else {
        // Handle error - cannot open file for reading
    }
    return livres;
}