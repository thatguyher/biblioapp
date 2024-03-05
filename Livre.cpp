#include "Livre.h"

#include <utility>
#include "utils.h"

#include <fstream>

const std::string FILE_LAST_LIVRE_NR = "lastLivreNr.txt";
int Livre::lastLivreNr = 0;


const std::string ETAT_EXPLOITABLE = "Exploitable";
const std::string ETAT_NON_EXPLOITABLE = "Non exploitable";

// Constructeur par défaut
Livre::Livre() : disponible(true),
                 etat(ETAT_NON_EXPLOITABLE),
                 dateCreation(getCurrentDate()) {
    loadLastLivreNr();
    lastLivreNr++;

    char empruntNr[5];
    sprintf(empruntNr, "%04d", lastLivreNr);

    // Create ID in format "LVR" + 4 digit number
    id = "LVR" + std::string(empruntNr);
    saveLastLivreNr();
}

// Constructeur avec paramètres
Livre::Livre(std::string auteur, std::string titre)
        : auteur(std::move(auteur)),
          titre(std::move(titre)),
          disponible(true),
          etat(ETAT_EXPLOITABLE),
          dateCreation(getCurrentDate()) {
    loadLastLivreNr();
    lastLivreNr++;

    char empruntNr[5];
    sprintf(empruntNr, "%04d", lastLivreNr);

    // Create ID in format "LVR" + 4 digit number
    id = "LVR" + std::string(empruntNr);
    saveLastLivreNr();
}

// Constructeur de copie
Livre::Livre(const Livre &autre)
        : auteur(autre.auteur),
          titre(autre.titre),
          disponible(autre.disponible),
          etat(autre.etat),
          dateCreation(autre.dateCreation),
          dateDernierEmprunt(autre.dateDernierEmprunt),
          dateRetour(autre.dateRetour) {
    loadLastLivreNr();
    lastLivreNr++;

    char empruntNr[5];
    sprintf(empruntNr, "%04d", lastLivreNr);

    // Create ID in format "LVR" + 4 digit number
    id = "LVR" + std::string(empruntNr);
    saveLastLivreNr();
}

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
void Livre::setAuteur(const std::string& aAuteur) {
    auteur = aAuteur;
}

void Livre::setTitre(const std::string& aTitre) {
    titre = aTitre;
}

void Livre::setDisponible(bool aDisponible) {
    disponible = aDisponible;
}

void Livre::setEtat(const std::string& aEtat) {
    etat = aEtat;
}

void Livre::setDateCreation(const std::string& aDateCreation) {
    dateCreation = aDateCreation;
}

void Livre::setDateDernierEmprunt(const std::string& aDateDernierEmprunt) {
    dateDernierEmprunt = aDateDernierEmprunt;
}

void Livre::setDateRetour(const std::string& aDateRetour) {
    dateRetour = aDateRetour;
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
