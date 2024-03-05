#include "utils.h"
#include <ctime>
#include <sstream>
#include <iomanip>

std::string getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    std::stringstream ss;
    ss << std::put_time(now, "%d/%m/%Y");
    return ss.str();
}

Emprunt preter(Etudiant* etudiant, Livre* livre, const std::string& dateRetour) {
    Emprunt newEmprunt(etudiant->getId(), livre->getId(), dateRetour);
    int statutEmprunt = livre->emprunter(newEmprunt.getEmpruntId(), dateRetour);
    if (statutEmprunt == 0){
        Emprunt::save(newEmprunt);
        std::cout << "\n> Le livre " + livre->getId() + " a ete prete a l'etudiant " + etudiant->getId() + "! ";
        std::cout << newEmprunt;
    } else if (statutEmprunt == 1){
        std::cout << "\n> Vous ne pouvez pas preter Le livre " + livre->getId() + " car le livre n'est pas disponible  !\n";
    } else{ // statutEmprunt == 2
        std::cout << "\n> Vous ne pouvez pas preter Le livre " + livre->getId() + " car le livre n'est pas en bon etat !\n";
    }
    return newEmprunt;
}

int rendre(Livre& livre){
    return livre.retourner();
}