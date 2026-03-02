#include "frigider.h"

Frigider::Frigider(): Electrocasnic(), areCongelator(false) {
    tip = "Frigider";
}

Frigider::Frigider(const string& marca, const string& model, int anFabricatie, double pretCatalog, bool congelator)
    : Electrocasnic("Frigider", marca, model, anFabricatie, pretCatalog), areCongelator(congelator) {}

void Frigider::afisare(ostream& out) const {
    Electrocasnic::afisare(out);
    out << "Are congelator: ";
    if (areCongelator) out << "DA";
    else out << "NU";

    out << "\n";
}