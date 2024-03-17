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
    std::string  empruntId = Emprunt::generateEmpruntId();
    Emprunt newEmprunt(empruntId, etudiant->getId(), livre->getId(), dateRetour);
    int statutEmprunt = livre->emprunter(newEmprunt.getEmpruntId(), dateRetour);
    if (statutEmprunt == 0) {
//        Emprunt::save(newEmprunt);
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

bool processCommand(const std::string &command, std::vector<Livre> *livres, std::vector<Etudiant> *etudiants,
                    std::vector<Emprunt> *emprunts) {
    // Parse the command from the input string
    std::map<std::string, std::map<std::string, std::string>> parsedCommand = split(command, " ");

    if (parsedCommand.empty())
        return true;

    // Get an iterator for the map
    auto it = parsedCommand.begin();
    std::string base = it->first;
    std::map<std::string, std::string> params = it->second;

    if (base == "sauvegarder") {
        sauvegarderActivite(livres, etudiants, emprunts);
        std::cout << "Sauvegarde effectuee avec succes !\n";
    }

    if (base == "lister-livres") {
        if (params.find("d") != params.end()) {
            std::cout << "Lister les livres par critere de disponibilite (disponible: " << params["d"] << ").\n";
            listerLivres(livres, params["d"] == "oui");
        } else {
            // If no -d argument, list all books
            std::cout << "Lister tous les livres.\n";
            listerAllLivres(livres);
        }
    }

    if (base == "creer-livre") { // Test: creer-livre -t Attaque-des-titans -a Yemp
        std::string titre = params["t"];
        std::string auteur = params["a"];
        std::string id = Livre::generateLivreId();

        Livre livre(id, auteur, titre);
        livres->push_back(livre);
        std::cout << "Livre cree avec succees !";
        std::cout << livre;
    }

    if (base == "modifier-livre") { // Example: modifier-livre -i identifiant -a NewAuthor -t NewTitle...
        std::string identifiant = params["i"];

        bool trouve = false;
        for (Livre &livre: *livres) {
            if (livre.getId() == identifiant) {
                trouve = true;
                mettreAjourLivre(livre, params);
                std::cout << "Livre modifie avec succes!\n";
                std::cout << livre;
                break;
            }
        }
        if (!trouve) {
            std::cout << "Aucun livre avec l'identifiant donne n'a ete trouve.\n";
        }
    }

    if (base == "supprimer-livre") { // Example: supprimer-livre -i IDENTIFIANT
        std::string identifiant = params["i"];

        // find and remove the book
        auto end = std::remove_if(livres->begin(), livres->end(), [&identifiant](Livre &livre) {
            return livre.getId() == identifiant;
        });

        // check if the book was found and removed
        if (end != livres->end()) {
            livres->erase(end, livres->end());
            std::cout << "Livre supprime avec succes!\n";

            // Now remove all loan records for this book and keep track of the id's of the deleted records
            std::vector<std::string> deletedLoanIds;
            auto endEmprunts = std::remove_if(emprunts->begin(), emprunts->end(), [&identifiant, &deletedLoanIds](Emprunt &emprunt) {
                bool toRemove = emprunt.getLivreId() == identifiant;
                if(toRemove) {
                    deletedLoanIds.push_back(emprunt.getEmpruntId());
                }
                return toRemove;
            });

            if(endEmprunts != emprunts->end()) {
                emprunts->erase(endEmprunts, emprunts->end());
                std::cout << "Les emprunts lies au livre ont ete supprimes, ci-dessous leurs identifiants." << "\n";
                for(const auto& deletedLoanId : deletedLoanIds) {
                    std::cout << deletedLoanId << ", ";
                }
                std::cout << "\n";
            } else {
                std::cout << "Aucun emprunt associe au livre n'a ete trouve.\n";
            }
        } else {
            std::cout << "Aucun livre avec l'identifiant donne n'a ete trouve.\n";
        }
    }

    if (base == "lister-emprunteurs") {
        if (params.find("i") != params.end()) {
            std::cout << "Lister les emprunteurs du livre " << params["i"] << ".\n";
            listerEmprunteurs(params["i"], etudiants, emprunts);
        } else {
            std::cout << "Veuillez renseigner un identifiant de livre.\n";
        }
    }

    if (base == "details-livre") {
        if (params.find("i") != params.end()) {
            std::string id = params["i"];
            std::cout << "Afficher les details du livre " << id;

            // Displaying book details
            auto it = std::find_if(livres->begin(), livres->end(),
                                   [&id](const Livre &livre) { return livre.getId() == id; });
            if (it != livres->end()) {
                std::cout << *it;
            } else {
                std::cout << "Aucun livre avec l'identifiant donne n'a ete trouve.\n";
            }

            std::cout << "|=== Etudiants ayant emprunte le livre ===|\n";
            listerEmprunteurs(id, etudiants, emprunts);
        } else {
            std::cout << "Veuillez renseigner un identifiant de livre.\n";
        }
    }

// --- Module etudiants
    if (base == "lister-etudiants") {
        // If no -d argument, list all books
        std::cout << "Lister tous les etudiants.\n";
        listerAllEtudiants(etudiants);
    }

    if (base == "creer-etudiant") {
        std::string etudiantId = Etudiant::generateEtudiantId();
        std::string nom = params["n"];
        std::string prenom = params["p"];
        std::string dateNaissance = params["dn"];
        std::string numeroTelephone = params["t"];
        std::string adresseResidence = params["addr"];
        std::string numeroMatricule = params["m"];
        std::string classe = params["c"];
        std::string filiere = params["f"];

        Etudiant etudiant(etudiantId, nom, prenom, dateNaissance, numeroTelephone, adresseResidence,
                          nullptr, numeroMatricule, classe, filiere);
        etudiants->push_back(etudiant);

        std::cout << "Etudiant cree avec succees !";
        std::cout << etudiant;
    }

    if (base == "lister-emprunts") {
        if (params.find("i") != params.end()) {
            std::cout << "Lister les livres empruntes par l'etudiant " << params["i"] << ".\n";
            listerEmprunts(params["i"], livres, emprunts);
        } else if (emprunts->empty()) {
            std::cout << "Il n'y a pas d'emprunts en ce moment.\n";
        } else {
            std::cout << "Lister les emprunts.";
            for (const Emprunt &emprunt: *emprunts) {
                std::cout << emprunt;
            }
        }
    }

    if (base == "modifier-etudiant") { // Example: modifier-etudiant -i IDENTIFIANT -n NewNom -p NewPrenom...
        std::string identifiant = params["i"];

        bool trouve = false;
        for (Etudiant &etudiant: *etudiants) {
            if (etudiant.getId() == identifiant) {
                trouve = true;
                mettreAjourEtudiant(etudiant, params);
                std::cout << "Etudiant modifie avec succes!";
                std::cout << etudiant;
                break;
            }
        }
        if (!trouve) {
            std::cout << "Aucun etudiant avec l'identifiant donne n'a ete trouve.\n";
        }
    }

    if (base == "details-etudiant") {
        if (params.find("i") != params.end()) {
            std::string id = params["i"];
            std::cout << "Afficher les details de l'etudiant " << id;

            // Displaying book details
            auto it = std::find_if(etudiants->begin(), etudiants->end(),
                                   [&id](const Etudiant &etudiant) { return etudiant.getId() == id; });
            if (it != etudiants->end()) {
                std::cout << *it;
            } else {
                std::cout << "Aucun etudiant avec l'identifiant donne n'a ete trouve.\n";
            }

            std::cout << "|=== Livres empruntes ===|\n";
            listerEmprunts(params["i"], livres, emprunts);
        } else {
            std::cout << "Veuillez renseigner un identifiant d' etudiant.\n";
        }
    }

    if (base == "supprimer-etudiant") { // Example: supprimer-etudiant -i IDENTIFIANT
        std::string identifiant = params["i"];

        // find and remove the student
        auto end = std::remove_if(etudiants->begin(), etudiants->end(), [&identifiant](Etudiant &etudiant) {
            return etudiant.getId() == identifiant;
        });

        // check if the student was found and removed
        if (end != etudiants->end()) {
            etudiants->erase(end, etudiants->end());
            std::cout << "Etudiant supprime avec succes!\n";

            // Now remove all loan records for this student and keep track of the id's of the deleted records
            std::vector<std::string> deletedLoanIds;
            auto endEmprunts = std::remove_if(emprunts->begin(), emprunts->end(), [&identifiant, &deletedLoanIds](Emprunt &emprunt) {
                if(emprunt.getEtudiantId() == identifiant) {
                    deletedLoanIds.push_back(emprunt.getEmpruntId());
                    return true;
                }
                return false;
            });

            if(endEmprunts != emprunts->end()) {
                emprunts->erase(endEmprunts, emprunts->end());
                std::cout << "Les emprunts lies au livre ont ete supprimes, ci-dessous leurs identifiants." << "\n";
                for(const auto& deletedLoanId : deletedLoanIds) {
                    std::cout << deletedLoanId << ", " << "\n";
                }
                std::cout << "\n";
            } else {
                std::cout << "Aucun emprunt associe a l'etudiant n'a ete trouve.\n";
            }
        } else {
            std::cout << "Aucun etudiant avec l'identifiant donne n'a ete trouve.\n";
        }
    }

    if (base == "preter") { // Example: preter -l IDENTIFIANT_LIVRE -e IDENTIFIANT_ETUDIANT -dr DATE_RETOUR

        std::string identifiantLivre = params["l"];
        std::string identifiantEtudiant = params["e"];
        std::string dateRetour = params["dr"];

        // Validate the book ID
        auto itLivre = std::find_if(livres->begin(), livres->end(),
                                    [&identifiantLivre](const Livre& livre) {
                                        return livre.getId() == identifiantLivre;
                                    });

        if (itLivre == livres->end()) {
            std::cout << "Aucun livre avec l'identifiant " << identifiantLivre << " n'a ete trouve.\n";
            return true;
        }

        // Validate the student ID
        auto itEtudiant = std::find_if(etudiants->begin(), etudiants->end(),
                                       [&identifiantEtudiant](const Etudiant& etudiant) {
                                           return etudiant.getId() == identifiantEtudiant;
                                       });

        if (itEtudiant == etudiants->end()) {
            std::cout << "Aucun etudiant avec l'identifiant " << identifiantEtudiant << " n'a ete trouve.\n";
            return true;
        }

        // Create a new loan
        std::string  empruntId = Emprunt::generateEmpruntId();
        Emprunt newEmprunt(empruntId, itEtudiant->getId(), itLivre->getId(), dateRetour);
        int statutEmprunt = itLivre->emprunter(newEmprunt.getEmpruntId(), dateRetour);
        if (statutEmprunt == 0) {
            std::cout << "Le livre " + itLivre->getId() + " a ete prete a l'etudiant " + itEtudiant->getId() + "! ";
            std::cout << newEmprunt;
        } else if (statutEmprunt == 1) {
            std::cout << "Vous ne pouvez pas preter Le livre " + itLivre->getId() +
                         " car le livre n'est pas disponible  !\n";
        } else { // statutEmprunt == 2
            std::cout << "Vous ne pouvez pas preter Le livre " + itLivre->getId() +
                         " car le livre n'est pas en bon etat ("  << itLivre->getEtat() << ") !\n";
        }

        // Save the loan in the list of loans
        emprunts->push_back(newEmprunt);
    }

    if (base == "recuperer") { // Exemple: recuperer -l IDENTIFIANT_LIVRE -e IDENTIFIANT_ETUDIANT

        std::string identifiantLivre = params["l"];
        std::string identifiantEtudiant = params["e"];

        // Find the correct loan
        auto itEmprunt = std::find_if(emprunts->begin(), emprunts->end(),
                                      [&identifiantLivre, &identifiantEtudiant](const Emprunt& emprunt) {
                                          return emprunt.getLivreId() == identifiantLivre
                                                 && emprunt.getEtudiantId() == identifiantEtudiant
                                                 && !emprunt.isEstRetourne();
                                      });

        if (itEmprunt == emprunts->end()) {
            std::cout << "Aucun emprunt en cours correspondant aux identifiants fournis n'a ete trouve.\n";
            return true;
        }

        // Validate that the book has not been returned yet
        if (itEmprunt->isEstRetourne()) {
            std::cout << "Ce livre a deja ete retourne.\n";
            return true;
        }

        // Update the loan to be returned
        itEmprunt->setEstRetourne(true);
        std::cout << "Le livre " + itEmprunt->getLivreId()
                     + " a ete retourne par l'etudiant " + itEmprunt->getEtudiantId() + " avec succes !\n";

        // Update the book to be available
        auto itLivre = std::find_if(livres->begin(), livres->end(),
                                    [&identifiantLivre](const Livre& livre) {
                                        return livre.getId() == identifiantLivre;
                                    });

        if (itLivre != livres->end()) {
            itLivre->retourner();
        }
    }

    if (base == "quitter" || base == "q") {
        std::cout << "> Etes vous sure de vouloire quitter l' application ? (entrez 'o' pour oui, 'n' pour non).\n";
        std::cout << "> ";
        std::string reponse;
        std::getline(std::cin, reponse);
        if (reponse == "o"){
            sauvegarderActivite(livres, etudiants, emprunts);
            std::cout << "Sauvegarde effectuee avec succes !\n";
            std::cout << "A bientot ! ";
            return false;
        }
    }

    if (base == "documentation" || base == "doc" || base == "aide") {
        std::cout << R"(

________                                             __          __  .__
\______ \   ____   ____  __ __  _____   ____   _____/  |______ _/  |_|__| ____   ____
 |    |  \ /  _ \_/ ___\|  |  \/     \_/ __ \ /    \   __\__  \\   __\  |/  _ \ /    \
 |    `   (  <_> )  \___|  |  /  Y Y  \  ___/|   |  \  |  / __ \|  | |  (  <_> )   |  \
/_______  /\____/ \___  >____/|__|_|  /\___  >___|  /__| (____  /__| |__|\____/|___|  /
        \/            \/            \/     \/     \/          \/                    \/

documentation ou doc ou aide: Afficher la documentation.

creer-livre -t TITRE -a AUTEUR : Cree un nouveau livre dans la bibliotheque.
    -t TITRE : Titre du livre.
    -a AUTEUR : Auteur du livre.

modifier-livre -i IDENTIFIANT [-t TITRE] [-a AUTEUR] : Modifie les informations d'un livre existant.
    -i IDENTIFIANT : Identifiant du livre a modifier.
    -t TITRE (optionnel) : Nouveau titre pour le livre.
    -a AUTEUR (optionnel) : Nouvel auteur pour le livre.

supprimer-livre -i IDENTIFIANT : Supprime un livre specifique de la bibliotheque et lister les identifiants des emprunts supprimes.
    -i IDENTIFIANT : Identifiant du livre a supprimer.

lister-livres [-d oui/non] : Liste tous les livres dans la bibliotheque.
    -d oui/non (optionnel) : Liste les livres en fonction de leur disponibilite. "oui" pour les livres disponibles, "non" pour les livres empruntes.

details-livre -i IDENTIFIANT : Affiche en detail les informations d'un livre specifique.
    -i IDENTIFIANT : Identifiant du livre.

lister-emprunteurs -i IDENTIFIANT : Liste tous les étudiants qui ont emprunte un livre specifique.
    -i IDENTIFIANT : Identifiant du livre.

creer-etudiant -n NOM -p PRENOM -dn DATE_NAISSANCE -t TELEPHONE -addr ADRESSE -m MATRICULE -c CLASSE -f FILIERE : Creer un nouvel etudiant.
    -n NOM : Nom de l'etudiant.
    -p PRENOM : Prénom de l'etudiant.
    -dn DATE_NAISSANCE : Date de naissance de l'etudiant.
    -t TELEPHONE : Numero de telephone de l'etudiant.
    -addr ADRESSE : Adresse residentielle de l'etudiant.
    -m MATRICULE : Numero de matricule de l'etudiant.
    -c CLASSE : Classe de l'etudiant.
    -f FILIERE : Filiere de l'etudiant.

modifier-etudiant -i IDENTIFIANT [...] : Modifie les informations d'un etudiant existant. Les informations pour la modification
suivent le meme format que pour creer-etudiant (a l'exception de -i IDENTIFIANT).

supprimer-etudiant -i IDENTIFIANT : Supprime un etudiant specifique et liste les identifiants des emprunts supprimes.
    -i IDENTIFIANT : Identifiant de l'etudiant.

lister-emprunts -i IDENTIFIANT : Liste tous les livres empruntes par un etudiant specifique.
    -i IDENTIFIANT : Identifiant de l'etudiant.

details-etudiant -i IDENTIFIANT : Affiche en detail les informations d'un etudiant specifique.
    -i IDENTIFIANT : Identifiant de l'etudiant.

lister-etudiants : Liste tous les etudiants.

preter -l IDENTIFIANT_LIVRE -e IDENTIFIANT_ETUDIANT -dr DATE_RETOUR : Emprunte un livre specifique a un etudiant specifique.
    -l IDENTIFIANT_LIVRE : Identifiant du livre.
    -e IDENTIFIANT_ETUDIANT : Identifiant de l'etudiant.
    -dr DATE_RETOUR : Date de retour prevue pour l'emprunt.

recuperer -l IDENTIFIANT_LIVRE -e IDENTIFIANT_ETUDIANT : Declare qu'un livre specifique a ete retourne par un etudiant specifique.
    -l IDENTIFIANT_LIVRE : Identifiant du livre.
    -e IDENTIFIANT_ETUDIANT : Identifiant de l'etudiant.

sauvegarder : Sauvegarde l'etat actuel de la bibliotheque (livres, etudiants, emprunts).

quitter ou q : Sauvegarde et quitte l'application.
)";
    }

    return true;
}
