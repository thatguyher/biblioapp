#include "Emprunt.h"
#include "utils.h"

#include <utility>
#include <fstream>

const std::string FILE_LAST_EMPRUNT_NR = "lastEmpruntNr.txt";
const std::string FILE_EMPRUNTS = "emprunts_file.DAAJ";
int Emprunt::lastEmpruntNr = 0;

// Constructeur par defaut
Emprunt::Emprunt() : empruntId(""), dateEmprunt(getCurrentDate()), estRetourne(0) {}

Emprunt::Emprunt(std::string id, std::string idEtudiant, std::string idLivre, std::string  aDateRetour)
        : empruntId(std::move(id)),
        etudiantId(std::move(idEtudiant)),
          livreId(std::move(idLivre)),
          dateEmprunt(getCurrentDate()),
          dateRetour(std::move(aDateRetour)),
          estRetourne(false) {}

std::string Emprunt::generateEmpruntId() {
    loadLastEmpruntNr();
    lastEmpruntNr++;

    char empruntNr[5];
    sprintf(empruntNr, "%04d", lastEmpruntNr);

    // Create ID in format "EMP" + 4 digit number
    std::string id = "EMP" + std::string(empruntNr);
    saveLastEmpruntNr();

    return id;
}

void Emprunt::loadLastEmpruntNr() {
    std::ifstream infile(FILE_LAST_EMPRUNT_NR);
    if (infile.good()) {
        infile >> lastEmpruntNr;
    }
    infile.close();
}

void Emprunt::saveLastEmpruntNr() {
    std::ofstream outfile(FILE_LAST_EMPRUNT_NR);
    if (outfile.good()) {
        outfile << lastEmpruntNr;
    }
    outfile.close();
}

int Emprunt::save(const Emprunt &emp) {
    std::ofstream outFile(FILE_EMPRUNTS, std::ios::app); // open file in append mode

    if (outFile.is_open()) {
        outFile << emp.getEmpruntId() << "\n"
                << emp.getEtudiantId() << "\n"
                << emp.getLivreId() << "\n"
                << emp.getDateEmprunt() << "\n"
                << emp.getDateRetour() << "\n"
                << emp.getEmpruntId() << "\n"
                << emp.isEstRetourne() << "\n"
                << "-----" << "\n";   // Add a separator between instances for readability
        outFile.close();
        return  0;
    } else {
        return  1;
    }
}

void Emprunt::saveMultiple(const std::vector<Emprunt>* emprunts) {
    // Open the file in overwrite mode.
    // Any previous content will be deleted.
    std::ofstream outFile(FILE_EMPRUNTS);
    outFile.close();

    for (const Emprunt &emp : *emprunts) {
        save(emp);
    }
}

std::vector<Emprunt> Emprunt::loadMultiple() {
    std::vector<Emprunt> emprunts;
    std::ifstream inFile(FILE_EMPRUNTS);
    std::string line;

    if (inFile.is_open()) {
        while (std::getline(inFile, line)) {
            Emprunt emp;
            if (!line.empty()) emp.setEmpruntId(line);
            if (std::getline(inFile, line)) emp.setEtudiantId(line);
            if (std::getline(inFile, line)) emp.setLivreId(line);
            if (std::getline(inFile, line)) emp.setDateEmprunt(line);
            if (std::getline(inFile, line)) emp.setDateRetour(line);
            if (std::getline(inFile, line)) emp.setEmpruntId(line);
            if (std::getline(inFile, line)) emp.setEstRetourne(line == "1");
            emprunts.push_back(emp);
            std::getline(inFile, line); // read the "-----" line (delimiter)
        }
        inFile.close();
    } else {
        // Handle error - cannot open file for reading
    }

    return emprunts;
}

const std::string &Emprunt::getLivreId() const {
    return livreId;
}

void Emprunt::setLivreId(const std::string &livreId) {
    Emprunt::livreId = livreId;
}

const std::string &Emprunt::getDateEmprunt() const {
    return dateEmprunt;
}

void Emprunt::setDateEmprunt(const std::string &dateEmprunt) {
    Emprunt::dateEmprunt = dateEmprunt;
}

const std::string &Emprunt::getDateRetour() const {
    return dateRetour;
}

void Emprunt::setDateRetour(const std::string &dateRetour) {
    Emprunt::dateRetour = dateRetour;
}

const std::string &Emprunt::getEtudiantId() const {
    return etudiantId;
}

void Emprunt::setEtudiantId(const std::string &etudiantId) {
    Emprunt::etudiantId = etudiantId;
}

bool Emprunt::isEstRetourne() const {
    return estRetourne;
}

void Emprunt::setEstRetourne(bool estRetourne) {
    Emprunt::estRetourne = estRetourne;
}

const std::string &Emprunt::getEmpruntId() const {
    return empruntId;
}

void Emprunt::setEmpruntId(const std::string &empruntId) {
    Emprunt::empruntId = empruntId;
}

int Emprunt::getLastEmpruntNr() {
    return lastEmpruntNr;
}

void Emprunt::setLastEmpruntNr(int lastEmpruntNr) {
    Emprunt::lastEmpruntNr = lastEmpruntNr;
}

void Emprunt::afficher() const {
    std::cout << "\n|=== EMPRUNT" << "\n";
    std::cout << "|-> ID: " << empruntId << "\n";
    std::cout << "|" << "\n";
    std::cout << "|-> Etudiant: " << etudiantId << "\n";
    std::cout << "|-> Livre: " << livreId << "\n";
    std::cout << "|-> Date d'emprunt: " << dateEmprunt << "\n";
    std::cout << "|-> Date de retour: " << dateRetour << "\n";
    std::cout << "|-> Statut: " << (estRetourne == 1 ? "Rendu" : "Non rendu")  << "\n";
    std::cout << "|===\n";
}

std::ostream &operator<<(std::ostream &os, const Emprunt &emprunt){
    emprunt.afficher();
    return os;
}
