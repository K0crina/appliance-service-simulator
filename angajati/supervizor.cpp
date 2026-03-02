#include "supervizor.h"

Supervizor::Supervizor() : Angajat() {}

Supervizor::Supervizor(int id, const string& nume, const string& prenume, const char* cnp,
    const string& dataAngajare, const string& domiciliu)
    : Angajat(id, nume, prenume, cnp, dataAngajare, domiciliu) {}

//salariu
double Supervizor::salariu() const {
    return Angajat::salariu() + 4000.0 * 0.20; // + sporul de conducere
}

//afisare
void Supervizor::afisare(ostream& out) const {
    out << "Tip Angajat: Supervizor \n";
    Angajat::afisare(out);
    out << "Salariu curent: " << salariu() << "\n";
}
