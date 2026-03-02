#include "tehnician.h"

Tehnician::Tehnician(): Angajat(), valoareReparatii(0.0) {}

Tehnician::Tehnician(int id, const string& nume, const string& prenume, const char* cnp, const string& dataAngajare, 
    const string& domiciliu): Angajat(id, nume, prenume, cnp, dataAngajare, domiciliu), valoareReparatii(0.0) {}

bool Tehnician::existaSpecializare(const string& tip, const string& marca) const {
    for (int i = 0; i < (int)tipuri.size(); i++)
        if (tipuri[i] == tip && marci[i] == marca)
            return true;

    return false;
}

void Tehnician::adaugaSpecializare(const string& tip, const string& marca) {
    if (existaSpecializare(tip, marca))
        return;

    tipuri.push_back(tip);
    marci.push_back(marca);
}

void Tehnician::stergeSpecializare(const string& tip, const string& marca) {
    for (int i = 0; i < (int)tipuri.size(); i++)
        if (tipuri[i] == tip && marci[i] == marca) {
            tipuri.erase(tipuri.begin() + i);
            marci.erase(marci.begin() + i);
            return;
        }
}

bool Tehnician::poateRepara(const string& tip, const string& marca) const {
    return existaSpecializare(tip, marca);
}

void Tehnician::adaugaReparatie(double valoare) {
    valoareReparatii += valoare;
}

double Tehnician::getValoareReparatii() const {
    return valoareReparatii;
}

double Tehnician::salariu() const {
    double bonus = 0.02 * valoareReparatii;

    return Angajat::salariu() + bonus;
}

void Tehnician::afisare(ostream& out) const {
    out << "Tip angajat: Tehnician\n";
    Angajat::afisare(out);

    out << "Specializari (tip - marca): ";
    
    if (tipuri.size() != 0)
        for (int i = 0; i < (int)tipuri.size(); i++) {
            out << tipuri[i] << " " << marci[i];
            if (i != (int)tipuri.size() - 1) 
                out << ", ";
        }

    out << "\n";

    out << "Valoarea reparatiilor efectuate: " << valoareReparatii << "\n";
    out << "Salariu curent: " << salariu() << "\n";
}