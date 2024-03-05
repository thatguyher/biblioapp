#include "utils.h"
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

void processCommand(const std::string &command) {
    // Parse the command from the input string
    std::map<std::string, std::map<std::string, std::string>> parsedCommand = split(command, " ");

    if (parsedCommand.empty())
        return;

    // Get an iterator for the map
    auto it = parsedCommand.begin();
    std::string base = it->first;
    std::map<std::string, std::string> params = it->second;

    //TODO: replace this example code with actual handling code based on your application requirements
    std::cout << "Processing command. Provided arguments:\n";
    std::cout << base << "\n";
    for (auto &pair: params) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
}
