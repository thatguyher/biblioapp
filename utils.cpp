#include "utils.h"
#include "actions.h"
#include <ctime>
#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>

std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);

    std::stringstream ss;
    ss << std::put_time(now, "%d/%m/%Y");
    return ss.str();
}

Emprunt preter(Etudiant *etudiant, Livre *livre, const std::string &dateRetour) {
    Emprunt newEmprunt(etudiant->getId(), livre->getId(), dateRetour);
    int statutEmprunt = livre->emprunter(newEmprunt.getEmpruntId(), dateRetour);
    if (statutEmprunt == 0) {
        Emprunt::save(newEmprunt);
        std::cout << "\n> Le livre " + livre->getId() + " a ete prete a l'etudiant " + etudiant->getId() + "! ";
        std::cout << newEmprunt;
    } else if (statutEmprunt == 1) {
        std::cout << "\n> Vous ne pouvez pas preter Le livre " + livre->getId() +
                     " car le livre n'est pas disponible  !\n";
    } else { // statutEmprunt == 2
        std::cout << "\n> Vous ne pouvez pas preter Le livre " + livre->getId() +
                     " car le livre n'est pas en bon etat !\n";
    }
    return newEmprunt;
}

int rendre(Livre &livre) {
    return livre.retourner();
}

// Function to split string str using given delimiter
std::map<std::string, std::map<std::string, std::string>> split(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> params;
    std::map<std::string, std::map<std::string, std::string>> command;
    std::map<std::string, std::string> keyValuePairs;

    size_t a = 0;
    size_t b = str.find(delimiter);
    while (b != std::string::npos) {
        params.push_back(str.substr(a, b - a));
        a = b + delimiter.length();
        b = str.find(delimiter, a);
    }
    params.push_back(str.substr(a));


    if (params.size() % 2 != 0) {
        for (std::size_t i = 1; i < params.size(); i += 2) {
            if (params[i][0] == '-') params[i].erase(0, 1);
            keyValuePairs.insert(std::make_pair(params[i], params[i + 1]));
        }
    }

    command.insert(std::make_pair(params[0], keyValuePairs));

    return command;
}

void processCommand(const std::string& command, std::vector<Livre>* livres, std::vector<Etudiant>* etudiants, std::vector<Emprunt>* emprunts) {
    // Parse the command from the input string
    std::map<std::string, std::map<std::string, std::string>> parsedCommand = split(command, " ");

    if (parsedCommand.empty())
        return;

    // Get an iterator for the map
    auto it = parsedCommand.begin();
    std::string base = it->first;
    std::map<std::string, std::string> params = it->second;

    if (base == "sauvegarder"){
        sauvegarderActivite(livres, etudiants, emprunts);
        std::cout << "Sauvegarde effectuee avec succes !\n";
    }

//    if (base == "lister-livres"){
//        listerLivres(livres);
//    }

    if (base == "lister-livres") {
        if (params.find("d") != params.end()) {
            std::cout << "Afficher les livres par critere de disponibilite (disponible: " << params["d"] << ").\n";
            listerLivres(livres, params["d"] == "oui");
        } else {
            // If no -d argument, list all books
            std::cout << "Afficher tous les livres.\n";
            listerAllLivres(livres);
        }
    }

    if (base == "creer-livre"){ // Test: creer-livre -t Attaque-des-titans -a Yemp
        std::string titre = params["t"];
        std::string auteur = params["a"];
        Livre livre(auteur, titre);
        livres->push_back(livre);
        std::cout << "Livre cree avec succees !";
        std::cout << livre;
    }

    if (base == "modifier-livre"){ // Example: modifier-livre -i identifiant -a NewAuthor -t NewTitle...
        std::string identifiant = params["i"];

        bool trouve = false;
        for(Livre& livre : *livres) {
            if(livre.getId() == identifiant) {
                trouve = true;
                mettreAjourLivre(livre, params);
                std::cout << "Livre modifie avec succes!\n";
                std::cout << livre;
                break;
            }
        }
        if (!trouve){
            std::cout << "Aucun livre avec l'identifiant donne n'a ete trouve.";
        }
    }

    if (base == "supprimer-livre") { // Example: supprimer-livre -i IDENTIFIANT
        std::string identifiant = params["i"];

        auto end = std::remove_if(livres->begin(), livres->end(), [&identifiant](Livre &livre) {
            return livre.getId() == identifiant;
        });

        if (end != livres->end()) {
            livres->erase(end, livres->end());
            std::cout << "Livre supprime avec succes!\n";
        } else {
            std::cout << "Aucun livre avec l'identifiant donne n'a ete trouve.\n";
        }
    }

//    std::cout << "Processing command. Provided arguments:\n";
//    std::cout << base << "\n";
//    for (auto &pair: params) {
//        std::cout << pair.first << ": " << pair.second << '\n';
//    }
}
