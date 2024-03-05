#include <locale>
#include <iostream>
#include "Personne.h"
#include "Etudiant.h"
#include "Emprunt.h"
#include "utils.h"

using namespace std;

int main() {
    // Activer l'encodage UTF-8 pour la sortie console
    std::locale::global(std::locale(""));

    std::cout << R"(


  ______   ______   ______   ______   ______   ______   ______   ______   ______   ______   ______   ______
 /_____/  /_____/  /_____/  /_____/  /_____/  /_____/  /_____/  /_____/  /_____/  /_____/  /_____/  /_____/


__________.__                                                     .___
\______   \__| ____   _______  __ ____   ____  __ __   ____     __| _/____    ____   ______
 |    |  _/  |/ __ \ /    \  \/ // __ \ /    \|  |  \_/ __ \   / __ |\__  \  /    \ /  ___/
 |    |   \  \  ___/|   |  \   /\  ___/|   |  \  |  /\  ___/  / /_/ | / __ \|   |  \\___ \
 |______  /__|\___  >___|  /\_/  \___  >___|  /____/  \___  > \____ |(____  /___|  /____  >
        \/        \/     \/          \/     \/            \/       \/     \/     \/     \/
__________._____.   .__  .__            _____                  ._.
\______   \__\_ |__ |  | |__| ____     /  _  \ ______ ______   | |
 |    |  _/  || __ \|  | |  |/  _ \   /  /_\  \\____ \\____ \  | |
 |    |   \  || \_\ \  |_|  (  <_> ) /    |    \  |_> >  |_> >  \|
 |______  /__||___  /____/__|\____/  \____|__  /   __/|   __/   __
        \/        \/                         \/|__|   |__|      \/


  ______   ______   ______   ______   ______   ______   ______
 /_____/  /_____/  /_____/  /_____/  /_____/  /_____/  /_____/

)";

    // Création d'une personne
//    Personne personne1("Doe", "John", "01/01/1990", "123456789", "123 Main Street", nullptr);
//
//    // Affichage des détails de la personne en utilisant l'opérateur <<
//    std::cout << personne1;
//
//    // Création d'une autre personne
//    Personne personne2("Mouse", "Pluto", "02/02/1995", "987654321", "456 Second Street", &personne1);
//
//    // Affichage des détails de la personne Pluto en invoquant l'opérateur <<
//    std::cout << personne2;
//
// Création d'un étudiant
//    Etudiant etudiant1("Doe", "John", "01/01/1995", "123456789", "123 Main Street", nullptr,
//                       "2021001", "Informatique", "Licence");

//    Etudiant::save(etudiant1);

//// Création d'un étudiant
//    Etudiant etudiant2("Doe", "John", "01/01/1995", "123456789", "123 Main Street", &personne1,
//                       "2021001", "Informatique", "Licence");
//
//    // Affichage des détails de l'étudiant
//    std::cout << etudiant1;
//    std::cout << etudiant2;

//    Livre book1;
//    Livre book2("George Orwell", "1984");
//
//    Livre::save(book2);
//    Livre::save(book2);
//    std::cout << book1;
//    std::cout << book2;

// Declare an instance of Emprunt
//
//    preter(&etudiant1,&book2, "2024-12-31");
//
//
//    std::cout << book2;

// Get command from user

    while (true) {
        std::cout << "Biblio Commande> ";
        std::string command;
        std::getline(std::cin, command);

        // Process the user's command
        processCommand(command);
    }

    return 0;
}