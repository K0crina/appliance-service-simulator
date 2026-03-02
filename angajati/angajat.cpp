#include "angajat.h"

int numar(char c) {
    return c - '0';
}

int varstaLaAngajare(const char* cnp, const string& dataAngajare) {
    if (cnp == nullptr)
        return -1;

    // extragem data nasterii din CNP
    int S  = numar(cnp[0]);
    int yy = numar(cnp[1]) * 10 + numar(cnp[2]);
    int mm = numar(cnp[3]) * 10 + numar(cnp[4]);
    int dd = numar(cnp[5]) * 10 + numar(cnp[6]);

    int anNastere = 1900 + yy;;

    if (S == 1 || S == 2)
        anNastere = 1900 + yy;
    else if (S == 5 || S == 6)
        anNastere = 2000 + yy;
    
    int ziA, lunaA, anA;
    data(dataAngajare, ziA, lunaA, anA);

    int varsta = anA - anNastere;

    if (lunaA < mm || (lunaA == mm && ziA < dd))
        varsta--;

    return varsta;
}

//validari
void Angajat::validareNume(const string& s) {
    if (s.size() < 3 || s.size() > 30)
        throw invalid_argument("Nume invalid: trebuie sa aiba de la 3 la 30 caractere.");
}

void Angajat::validarePrenume(const string& s) {
    if (s.size() < 3 || s.size() > 30)
        throw invalid_argument("Prenume invalid: trebuie sa aiba de la 3 la 30 caractere.");
}

void Angajat::validareCNP(const char* c) {
    if (c == nullptr)
        throw invalid_argument("CNP invalid: null.");

    if (strlen(c) != 13)
        throw invalid_argument("CNP invalid: trebuie sa aiba 13 cifre.");

    for (int i = 0; i < 13; i++) {
        if (!isdigit(c[i]))
            throw invalid_argument("CNP invalid: contine caractere non-cifra.");
    }

    // cifra de control
    const char* k = "279146358279";
    int sum = 0;

    for (int i = 0; i < 12; i++)
        sum += numar(c[i]) * numar(k[i]);

    int rest = sum % 11;
    int control = 0;
    
    if (rest < 10) control = rest;
    else if (rest == 10) control = 1;

    if (numar(c[12]) != control)
        throw invalid_argument("CNP invalid: cifra de control gresita.");
}

//constructori
Angajat::Angajat(): id(0), nume(""), prenume(""), dataAngajare(""), domiciliu("") {
    cnp[0] = '\0';
}

Angajat::Angajat(int ID, const string& n, const string& p, const char* c,const string& dA,
    const string& d): id(ID), nume(n), prenume(p), dataAngajare(dA), domiciliu(d) {
    
    if (id <= 0)
        throw invalid_argument("ID invalid: trebuie > 0.");

    validareNume(nume);
    validarePrenume(prenume);

    if (domiciliu.size() < 2)
        throw invalid_argument("Domiciliu invalid.");

    int z, l, a;
    data(dataAngajare, z, l, a);

    validareCNP(c);
    strcpy(cnp, c);

    int varsta = varstaLaAngajare(cnp, dataAngajare);
    if (varsta < 16) {
        throw invalid_argument("Angajat prea tanar: trebuie sa aiba cel putin 16 ani la angajare.");
    }
}

//getters
int Angajat::getId() const {
    return id; 
}

const string& Angajat::getNume() const {
    return nume; 
}

const string& Angajat::getPrenume() const {
    return prenume;
}

const char* Angajat::getCNP() const {
    return cnp; 
}

const string& Angajat::getDataAngajare() const {
    return dataAngajare;
}

const string& Angajat::getDomiciliu() const {
    return domiciliu;
}

//modif nume
void Angajat::setNume(const string& n) {
    validareNume(n);
    nume = n;
}

//salariu la general
double Angajat::salariu() const {
    double baza = 4000.0;

    double transport = 0.0;
    if (domiciliu != "Bucuresti")
        transport = 400.0;

    int aniVechime = vechime(dataAngajare);
    int nivel = aniVechime / 3;  // la fiecare 3 ani
    double fidelitate = baza * (0.05 * nivel);

    return baza + transport + fidelitate;
}

//afisare
void Angajat::afisare(ostream& out) const {
    out << "ID: " << id << "\n";
    out << "Nume: " << nume << "\n";
    out << "Prenume: " << prenume << "\n";
    out << "CNP: " << cnp << "\n";
    out << "Domiciliu: " << domiciliu << "\n";
    out << "Data angajare: " << dataAngajare << "\n";
}

ostream& operator<<(ostream& out, const Angajat& a) {
    a.afisare(out);
    return out;
}
