#pragma once

#include "angajat.h"

class Supervizor: public Angajat {
public:
    Supervizor();
    Supervizor(int id,
               const string& nume,
               const string& prenume,
               const char* cnp,
               const string& dataAngajare,
               const string& domiciliu);

    // override = suprascriem functia virtuala pura din Angajat
    double salariu() const override;

    void afisare(ostream& out) const override;

};