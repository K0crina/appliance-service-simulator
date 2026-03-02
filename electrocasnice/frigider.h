#pragma once

#include "electrocasnic.h"

class Frigider: public Electrocasnic {
private:
    bool areCongelator;
public:
    Frigider();
    Frigider(const string& marca,
             const string& model,
             int anFabricatie,
             double pretCatalog,
             bool areCongelator);

    // afisare polimorfica (se adauga atributul specific)
    void afisare(ostream& out) const override;

};