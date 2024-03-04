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

    // Affichage des détails de la personne
    personne1.afficher();

    return 0;
}