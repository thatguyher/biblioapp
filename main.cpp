#include <locale>
#include <iostream>
#include "Personne.h"
#include "Etudiant.h"
#include "Emprunt.h"
#include "utils.h"

using namespace std;

int main() {
    // Activer l'encodage UTF-8 pour la sortie console
//    std::locale::global(std::locale("en_US.UTF-8"));
    std::locale::global(std::locale(""));

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
    Etudiant etudiant1("Doe", "John", "01/01/1995", "123456789", "123 Main Street", nullptr,
                       "2021001", "Informatique", "Licence");

//// Création d'un étudiant
//    Etudiant etudiant2("Doe", "John", "01/01/1995", "123456789", "123 Main Street", &personne1,
//                       "2021001", "Informatique", "Licence");
//
//    // Affichage des détails de l'étudiant
//    std::cout << etudiant1;
//    std::cout << etudiant2;

//    Livre book1;
    Livre book2("George Orwell", "1984");
//    std::cout << book1;
    std::cout << book2;

// Declare an instance of Emprunt

    preter(&etudiant1,&book2, "2024-12-31");


    std::cout << book2;

    return 0;
}