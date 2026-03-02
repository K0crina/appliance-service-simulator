#pragma once

#include "data.h"

class Angajat {
protected:
    int id;       // unic, nemodificabil
    string nume;
    string prenume;
    char cnp[14];   // 13 cifre + '\0' (fix)

    string dataAngajare; 
    string domiciliu;

    static void validareNume(const string& s);
    static void validarePrenume(const string& s);
    static void validareCNP(const char* cnp);

public:
    Angajat();
    Angajat(int id,
            const string& nume,
            const string& prenume,
            const char* cnp,
            const string& dataAngajare,
            const string& domiciliu);

    virtual ~Angajat() = default; // destructor virtual pt polimorfism

    // getteri
    int getId() const;
    const string& getNume() const;        // nu las pe nimeni sa modifice ce returnez + nu modific obiectul + !! EVITA COPIEREA
    const string& getPrenume() const;
    const char* getCNP() const;
    const string& getDataAngajare() const;
    const string& getDomiciliu() const;

    // modificare nume
    void setNume(const string& n);

    // functie virtuala pura => clasa abstracta
    virtual double salariu() const;

    virtual void afisare(ostream& out) const;
    friend ostream& operator<<(ostream& out, const Angajat& a);
};