#ifndef BIBLIOAPP_UTILS_H
#define BIBLIOAPP_UTILS_H

#include <string>
#include "Emprunt.h"

#include <map>

std::string getCurrentDate();

Emprunt preter(Etudiant* etudiant, Livre* livre, const std::string& date);

// Function to split string str using given delimiter
std::map<std::string, std::map<std::string, std::string>> split(const std::string &str, const std::string &delimiter);

void processCommand(const std::string& command);

#endif //BIBLIOAPP_UTILS_H
