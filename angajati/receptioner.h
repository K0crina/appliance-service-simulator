#pragma once

#include "angajat.h"
#include <vector>

class Receptioner: public Angajat {
private:
    vector<int> idCereri; // // lista cu ID urile cererilor inregistrate de el

public:
    Receptioner();
    Receptioner(int id,
                const string& nume,
                const string& prenume,
                const char* cnp,
                const string& dataAngajare,
                const string& domiciliu);

    // adauga un ID in lista
    void adaugaCerere(int id);

    // sterge un ID din lista (daca exista)
    void stergeCerere(int id);

    // getter optional ca sa vad lista
    const vector<int>& getIdCereri() const;

    double salariu() const override;
    void afisare(ostream& out) const override;
};