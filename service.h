#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "angajati/angajat.h"
#include "angajati/receptioner.h"
#include "angajati/tehnician.h"
#include "angajati/supervizor.h"
#include "cerereReparatie.h"

using namespace std;

class Service {
private:
    vector<unique_ptr<Angajat>> angajati;

    vector<unique_ptr<CerereReparatie>> cereri;

    int timpCurent;    // timp curent al simularii (secunda)

    // cauta dupa id
    Receptioner* gasesteReceptioner(int idRec);

    Tehnician* repartizareTehnician(const CerereReparatie& cerere);

public:
    Service();

    bool serviceFunctional() const;    // minim 3 tehnicieni, un receptionier si un supervizor

    Tehnician* gasesteTehnician(int idTeh);

    // gestiune angajati

    void adaugaAngajat(unique_ptr<Angajat> angajatNou);

    // dupa cnp
    bool stergeAngajat(const string& cnp);
    Angajat* cautaAngajat(const string& cnp) const;
    void afiseazaDetaliiAngajat(const string& cnp, ostream& out) const;

    void afiseazaTotiAngajatii(ostream& out) const;

    // gestiune cereri

    // o insereaza in vector, o adauga in lista receptionerului + incearca repartizarea catre un tehnician
    void adaugaCerere(unique_ptr<CerereReparatie> cerereNoua);

    void afiseazaCereri(ostream& out) const;

    // simulare pe secunde
    // scade durata ramasa pentru cererile active, finalizeaza cererile terminate + incearca sa repartizeze cereri in asteptare 
    void simulare(ostream& out);

    int getTimpCurent() const;
};
