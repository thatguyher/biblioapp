// -*- coding: utf-8 -*-

#include <locale>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include "Personne.h"

using namespace std;

int main()
{
    // Activer l'encodage UTF-8 pour la sortie console
    std::locale::global(std::locale("en_US.UTF-8"));


    // Création d'une personne
    Personne personne1("Doe", "John", "01/01/1990", "123456789", "123 Main Street", nullptr);

    // Affichage des détails de la personne en utilisant l'opérateur <<
    std::cout << personne1;

    // Création d'une autre personne
    Personne personne2("Mouse", "Pluto", "02/02/1995", "987654321", "456 Second Street", &personne1);

    // Affichage des détails de la personne Pluto en invoquant l'opérateur <<
    std::cout << personne2;

    return 0;
}