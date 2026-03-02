#include "masinaSpalat.h"

MasinaSpalat::MasinaSpalat(): Electrocasnic(), capacitate(0.0) {
    tip = "Masina de Spalat";
}

// constructor cu parametri
MasinaSpalat::MasinaSpalat(const string& marca, const string& model, int anFabricatie, double pretCatalog, double cap)
    : Electrocasnic("MasinaSpalat", marca, model, anFabricatie, pretCatalog), capacitate(cap) {}

void MasinaSpalat::afisare(ostream& out) const {
    Electrocasnic::afisare(out);
    out << "Capacitate: " << capacitate << " kg\n";
}