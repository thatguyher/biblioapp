
#include <vector>
#include <map>
#include "Livre.h"
#include "Etudiant.h"
#include "Emprunt.h"


void sauvegarderActivite(std::vector<Livre>* livres, std::vector<Etudiant>* etudiants, std::vector<Emprunt>* emprunts){
    Livre::saveMultiple(livres);
    Etudiant::saveMultiple(etudiants);
    Emprunt::saveMultiple(emprunts);
}

void listerLivres(std::vector<Livre>* livres, bool onlyAvailable = false) {
    int i = 0;
    for (const Livre& livre : *livres) {
        if (livre.isDisponible() == onlyAvailable) { // si onlyAvailable est false (faux), la condition sera toujours vraie.
            i++;
            std::cout << i << ".";
            std::cout << livre << "\n";
        }
    }
}

void listerAllLivres(std::vector<Livre>* livres) {
    int i = 0;
    for (const Livre& livre : *livres) {
        i++;
        std::cout << i << ".";
        std::cout << livre << "\n";
    }
}

void mettreAjourLivre(Livre& livre, std::map<std::string, std::string> params){
    // Author
    if(params.find("a") != params.end()) {
        std::string newAuteur = params["a"];
        // Add any validation you need for the new author
        livre.setAuteur(newAuteur);
    }
    // Title
    if(params.find("t") != params.end()) {
        std::string newTitle = params["t"];
        // Add any validation you need for the new title
        livre.setTitre(newTitle);
    }
    // Availability
    if(params.find("d") != params.end()) {
        bool newDisponible = params["d"] == "oui"; // Example: treat "oui" as true, everything else as false
        livre.setDisponible(newDisponible);
    }
    // State
    if(params.find("e") != params.end()) {
        std::string newEtat = params["e"];
        if(newEtat == "exploitable" || newEtat == "non-exploitable") {
            livre.setEtat(newEtat);
        }
    }

    // Return date
    if(params.find("dr") != params.end()) {
        std::string newDateRetour = params["dr"];
        // Add any validation you need for new date
        livre.setDateRetour(newDateRetour);
    }
}

void listerEmprunteurs(const std::string& identifiantLivre, std::vector<Etudiant>* etudiants, std::vector<Emprunt>* emprunts) {
    int count = 0;
    for (const auto& emprunt : *emprunts) {
        if (emprunt.getLivreId() == identifiantLivre && !emprunt.isEstRetourne()) {
            std::string etudiantId = emprunt.getEtudiantId();
            for (const auto& etudiant : *etudiants) {
                if (etudiant.getId() == etudiantId) {
                    count++;
                    std::cout << etudiant;
                    std::cout << emprunt << std::endl;
                }
            }
        }
    }
    if (count == 0){
        std::cout << "Aucun !" << std::endl;
    }
}

void listerEmprunts(const std::string& identifiantEtudiant, std::vector<Livre>* livres, std::vector<Emprunt>* emprunts) {
    int count = 0;
    for (const auto& emprunt : *emprunts) {
        if (emprunt.getEtudiantId() == identifiantEtudiant && !emprunt.isEstRetourne()) {
            std::string livreId = emprunt.getLivreId();
            for (const auto& livre : *livres) {
                if (livre.getId() == livreId) {
                    count++;
                    std::cout << livre;
                    std::cout << emprunt << std::endl;
                }
            }
        }
    }
    if (count == 0){
        std::cout << "Aucun emprunt\n";
    }
}

// The Etudiant updating function
void mettreAjourEtudiant(Etudiant& etudiant, std::map<std::string, std::string> params) {
    if (params.find("n") != params.end()) {
        std::string newNom = params["n"];
        etudiant.setNom(newNom);
    }

    if (params.find("p") != params.end()) {
        std::string newPrenom = params["p"];
        etudiant.setPrenom(newPrenom);
    }

    if (params.find("dn") != params.end()) {
        std::string newDateNaissance = params["dn"];
        etudiant.setDateNaissance(newDateNaissance);
    }

    if (params.find("t") != params.end()) {
        std::string newNumeroTelephone = params["t"];
        etudiant.setNumeroTelephone(newNumeroTelephone);
    }

    if (params.find("addr") != params.end()) {
        std::string newAdresseResidence = params["addr"];
        etudiant.setAdresseResidence(newAdresseResidence);
    }

    if (params.find("m") != params.end()) {
        std::string newNumeroMatricule = params["m"];
        etudiant.setNumeroMatricule(newNumeroMatricule);
    }

    if (params.find("c") != params.end()) {
        std::string newClasse = params["c"];
        etudiant.setClasse(newClasse);
    }

    if (params.find("f") != params.end()) {
        std::string newFiliere = params["f"];
        etudiant.setFiliere(newFiliere);
    }
}

void listerAllEtudiants(std::vector<Etudiant>* etudiants){
    int i = 0;
    for (const Etudiant& etudiant : *etudiants) {
        i++;
        std::cout << i << ".";
        std::cout << etudiant << "\n";
    }
}