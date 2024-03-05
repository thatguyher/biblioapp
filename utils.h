#ifndef BIBLIOAPP_UTILS_H
#define BIBLIOAPP_UTILS_H

#include <string>
#include "Emprunt.h"

std::string getCurrentDate();

Emprunt preter(Etudiant* etudiant, Livre* livre, const std::string& date);

#endif //BIBLIOAPP_UTILS_H
