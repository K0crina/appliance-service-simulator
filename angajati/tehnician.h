#pragma once

#include "angajat.h"
#include <vector>

class Tehnician : public Angajat {
private:
    vector<string> tipuri;
    vector<string> marci;

    double valoareReparatii;    // pt salariu

    bool existaSpecializare(const string& tip, const string& marca) const;

public:
    Tehnician();
    Tehnician(int id,
              const string& nume,
              const string& prenume,
              const char* cnp,
              const string& dataAngajare,
              const string& domiciliu);

    // adauga o specializare (tip, marca)
    void adaugaSpecializare(const string& tip, const string& marca);

    // sterge o specializare daca exista
    void stergeSpecializare(const string& tip, const string& marca);

    // verifica daca poate repara 
    bool poateRepara(const string& tip, const string& marca) const;

    // cand se termina o reparatie, adaugam valoarea ei aici
    void adaugaReparatie(double valoare);

    double getValoareReparatii() const;

    double salariu() const override;
    void afisare(ostream& out) const override;

};