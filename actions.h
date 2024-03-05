//
// Created by User on 3/5/2024.
//

#include <map>
#include "Livre.h"
#include "Etudiant.h"
#include "Emprunt.h"

#ifndef BIBLIOAPP_ACTIONS_H
#define BIBLIOAPP_ACTIONS_H

void listerAllLivres(std::vector<Livre>* livres);
void listerLivres(std::vector<Livre>* livres, bool onlyAvailable = false);
void mettreAjourLivre(Livre& livre, std::map<std::string, std::string> params);
void sauvegarderActivite(std::vector<Livre>* livres, std::vector<Etudiant>* etudiants, std::vector<Emprunt>* emprunts);
void listerEmprunteurs(const std::string& identifiantLivre, std::vector<Etudiant>* etudiants, std::vector<Emprunt>* emprunts);
void listerEmprunts(const std::string& identifiantEtudiant, std::vector<Livre>* livres, std::vector<Emprunt>* emprunts);

#endif //BIBLIOAPP_ACTIONS_H
