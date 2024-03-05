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

    // Charger les livres de l'application depuis le fichier de sauvegarde
    std::vector<Livre> biblioLivres(Livre::loadMultiple());
    // Charger les etudiants de l'application depuis le fichier de sauvegarde
    std::vector<Etudiant> biblioEtudiants(Etudiant::loadMultiple());
    // Charger les emprunts de l'application depuis le fichier de sauvegarde
    std::vector<Emprunt> biblioEmprunts(Emprunt::loadMultiple());

    bool go = true;
    while (go) {
        std::cout << "\n[Biblio] Commande> ";
        std::string command;
        std::getline(std::cin, command);

        // Process the user's command
         go = processCommand(command, &biblioLivres, &biblioEtudiants, &biblioEmprunts);
    }

    return 0;
}