#include "televizor.h"

Televizor::Televizor(): Electrocasnic(), diagonala(0.0), unitate("") {
    tip = "Televizor";
}

// constructor cu parametri
Televizor::Televizor(const string& marca, const string& model, int anFabricatie, double pretCatalog, double d, const string& u)
    : Electrocasnic("Televizor", marca, model, anFabricatie, pretCatalog), diagonala(d), unitate(u) {}

void Televizor::afisare(ostream& out) const {
    Electrocasnic::afisare(out);
    out << "Diagonala: " << diagonala << " " << unitate << "\n";
}







