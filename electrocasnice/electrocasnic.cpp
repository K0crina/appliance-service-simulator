#include "electrocasnic.h"

Electrocasnic::Electrocasnic(): tip(""), marca(""), model(""), anFabricatie(0), pretCatalog(0.0) {}

Electrocasnic::Electrocasnic(const string& t, const string& m, const string& mod, int an, double pret)
    : tip(t), marca(m), model(mod), anFabricatie(an), pretCatalog(pret) {}

//getteri
string Electrocasnic::getTip() const {
    return tip;
}

string Electrocasnic::getMarca() const {
    return marca;
}

string Electrocasnic::getModel() const {
    return model;
}

int Electrocasnic::getAnFabricatie() const {
    return anFabricatie;
}

double Electrocasnic::getPretCatalog() const {
    return pretCatalog;
}

//afisare
void Electrocasnic::afisare(ostream& out) const {
    out << "Tip electrocasnic: " << tip << "\n";
    out << "Marca: " << marca << "\n";
    out << "Model: " << model << "\n";
    out << "An fabricatie: " << anFabricatie << "\n";
    out << "Pret catalog: " << pretCatalog << "\n";
}

ostream& operator<<(ostream& out, const Electrocasnic& e) {
    e.afisare(out);
    return out;
}