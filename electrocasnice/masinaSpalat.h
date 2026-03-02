#pragma once

#include "electrocasnic.h"

class MasinaSpalat: public Electrocasnic {
private:
    double capacitate;

public:
    MasinaSpalat();
    MasinaSpalat(const string& marca,
                 const string& model,
                 int anFabricatie,
                 double pretCatalog,
                 double cap);
    
    void afisare(ostream& out) const override;
};