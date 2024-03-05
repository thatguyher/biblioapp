#ifndef BIBLIOAPP_EMPRUNT_H
#define BIBLIOAPP_EMPRUNT_H

#include <string>
#include "Etudiant.h"
#include "Livre.h"

class Emprunt {
public:
    Emprunt();
    Emprunt(std::string idEtudiant, std::string idLivre, std::string  aDateRetour);

    static void loadLastEmpruntNr();
    static void saveLastEmpruntNr();

    static int lastEmpruntNr;

    static int save(const Emprunt &emp);
    static void saveMultiple(const std::vector<Emprunt>* emprunts);
    static std::vector<Emprunt> loadMultiple();

    const std::string &getLivreId() const;

    void setLivreId(const std::string &livreId);

    const std::string &getDateEmprunt() const;

    void setDateEmprunt(const std::string &dateEmprunt);

    const std::string &getDateRetour() const;

    void setDateRetour(const std::string &dateRetour);

    const std::string &getEtudiantId() const;

    void setEtudiantId(const std::string &etudiantId);

    bool isEstRetourne() const;

    void setEstRetourne(bool estRetourne);

    const std::string &getEmpruntId() const;

    void setEmpruntId(const std::string &empruntId);

    static int getLastEmpruntNr();

    static void setLastEmpruntNr(int lastEmpruntNr);

    void afficher() const;

//    Surcharge des operateurs
    // L'pérateurs <<
    friend std::ostream &operator<<(std::ostream &os, const Emprunt &emprunt);

private:
    std::string livreId;
    std::string dateEmprunt;
    std::string dateRetour;
    std::string etudiantId;
    bool estRetourne; // 0 or 1
    std::string empruntId; // ID for each instance
};

#endif //BIBLIOAPP_EMPRUNT_H