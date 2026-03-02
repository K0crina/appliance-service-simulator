#pragma once

#include "electrocasnic.h"

class Televizor: public Electrocasnic {
private:
    double diagonala;
    string unitate;   // cm sau inch

public:
    Televizor();
    Televizor(const string& marca,
              const string& model,
              int anFabricatie,
              double pretCatalog,
              double diagonala,
              const string& unitate);

    void afisare(ostream& out) const override;
};