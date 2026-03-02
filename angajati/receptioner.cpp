#include "receptioner.h"

Receptioner::Receptioner() : Angajat() {}

Receptioner::Receptioner(int id, const string& nume, const string& prenume, const char* cnp, const string& dataAngajare,
    const string& domiciliu): Angajat(id, nume, prenume, cnp, dataAngajare, domiciliu) {}

// adaugare cerere
void Receptioner::adaugaCerere(int id) {
    if (id <= 0)
        throw invalid_argument("ID cerere invalid: trebuie > 0.");

    // verificam daca exista un duplicat
    for (int i = 0; i < (int)idCereri.size(); i++) {
        if (idCereri[i] == id)
            return; // deja exista, nu mai adaug
    }

    idCereri.push_back(id);
}

// stergere cerere (daca exista)
void Receptioner::stergeCerere(int id) {
    for (int i = 0; i < (int)idCereri.size(); i++)
        if (idCereri[i] == id) {
            idCereri.erase(idCereri.begin() + i);
            return;
        }
}

const vector<int>& Receptioner::getIdCereri() const {
    return idCereri;
}

double Receptioner::salariu() const {
    return Angajat::salariu();
}

void Receptioner::afisare(ostream& out) const {
    out << "Tip Angajat: Receptioner\n";
    Angajat::afisare(out);

    out << "Cereri inregistrate (ID-uri): ";

    if (idCereri.size() != 0)
        for (int i = 0; i < (int)idCereri.size(); i++) {
            out << idCereri[i];
            if (i != (int)idCereri.size() - 1) 
                out << ", ";
        }

    out << "\n";

    out << "Salariu curent: " << salariu() << "\n";
}
