#pragma once

#include "service.h"

#include <algorithm>
#include <stdexcept>
#include <cstring>

using namespace std;

Service::Service() : timpCurent(0) {}

bool Service::serviceFunctional() const {
    int nrTech = 0;
    int nrRec  = 0;
    int nrSup  = 0;

    for (int i = 0; i < angajati.size(); i++) {
        Tehnician* t = dynamic_cast<Tehnician*>(angajati[i].get());
        if (t != nullptr)
            nrTech++;
    }

    for (int i = 0; i < angajati.size(); i++) {
        Receptioner* r = dynamic_cast<Receptioner*>(angajati[i].get());
        if (r != nullptr)
            nrRec++;
    }

    for (int i = 0; i < angajati.size(); i++) {
        Supervizor* s = dynamic_cast<Supervizor*>(angajati[i].get());
        if (s != nullptr)
            nrSup++;
        
    }

    return (nrTech >= 3 && nrRec >= 1 && nrSup >= 1);
}

//gestiune angajati

void Service::adaugaAngajat(unique_ptr<Angajat> angajatNou) {
    angajati.push_back(move(angajatNou));
}

bool Service::stergeAngajat(const string& cnp) {
    for (int i = 0; i < angajati.size(); i++) {
        const char* cnpAng = angajati[i]->getCNP();
        if (cnpAng && strcmp(cnpAng, cnp.c_str()) == 0) {
            angajati.erase(angajati.begin() + static_cast<int>(i));
            return true;
        }
    }

    return false;
}

Angajat* Service::cautaAngajat(const string& cnp) const {
    for (int i = 0; i < angajati.size(); i++) {
        const char* cnpAng = angajati[i]->getCNP();
        if (cnpAng && strcmp(cnpAng, cnp.c_str()) == 0) {
            return angajati[i].get();
        }
    }

    return nullptr;
}

void Service::afiseazaDetaliiAngajat(const string& cnp, ostream& out) const {
    Angajat* a = cautaAngajat(cnp);
    if (!a) {
        out << "Nu exista angajat cu CNP: " << cnp << "\n";
        return;
    }

    a->afisare(out);
    out << "Salariu: " << a->salariu() << "\n";
}

void Service::afiseazaTotiAngajatii(ostream& out) const {
    for (int i = 0; i < angajati.size(); i++) {
        out << "\n";
        angajati[i]->afisare(out);
        out << "Salariu: " << angajati[i]->salariu() << "\n";
    }
}

Receptioner* Service::gasesteReceptioner(int idRec) {
    for (int i = 0; i < angajati.size(); i++) {
        Receptioner* r = dynamic_cast<Receptioner*>(angajati[i].get());
        if (r != nullptr && r->getId() == idRec)
            return r;
    }

    return nullptr;
}

Tehnician* Service::gasesteTehnician(int idTeh) {
    for (int i = 0; i < angajati.size(); i++) {
        Tehnician* t = dynamic_cast<Tehnician*>(angajati[i].get());
        if (t != nullptr && t->getId() == idTeh)
            return t;
    }

    return nullptr;
}

// calculeaza cate cereri active are un tehnician + timpul ramas
static void infoTeh(const vector<unique_ptr<CerereReparatie>>& cereri, int idTeh, int& nrActive,
                                  int& timpRamas) {
    nrActive = 0;
    timpRamas = 0;

    for (int i = 0; i < cereri.size(); i++) {
        const CerereReparatie* c = cereri[i].get();
        if (c->getIdTehnician() == idTeh && c->getStatus() == "ACTIVA") {
            nrActive++;
            timpRamas += c->getDurataRamasa();
        }
    }
}

Tehnician* Service::repartizareTehnician(const CerereReparatie& cerere) {
    const Electrocasnic* e = cerere.getElectrocasnic();
    if (!e)
        return nullptr;

    string tip   = e->getTip();
    string marca = e->getMarca();

    Tehnician* candidat = nullptr;
    int timpMin = 0;
    int nrActiveMin = 0;

    for (int i = 0; i < angajati.size(); i++) {
        Tehnician* t = dynamic_cast<Tehnician*>(angajati[i].get());
        if (!t) 
            continue;

        // verificam daca poate repare
        if (!t->poateRepara(tip, marca)) 
            continue;

        // verificam cereri active (maxim 3)
        int nrActive = 0;
        int timpRamas = 0;
        infoTeh(cereri, t->getId(), nrActive, timpRamas);

        if (nrActive >= 3) 
            continue;

        // verificam daca avem deja un candidat
        if (!candidat) {
            candidat = t;
            timpMin = timpRamas;
            nrActiveMin = nrActive;
        } else {
            // comparam cu tehnicianul curent t

            if (timpRamas < timpMin) {
                candidat = t;
                timpMin = timpRamas;
                nrActiveMin = nrActive;
            } else if (timpRamas == timpMin && nrActive < nrActiveMin) {
                candidat = t;
                timpMin = timpRamas;
                nrActiveMin = nrActive;
            }
        }
    }

    return candidat;
}

//gestiune cereri

void Service::adaugaCerere(unique_ptr<CerereReparatie> cerereNoua) {
    time_t ts = cerereNoua->getTimestamp();

    // inseram in vector crescator in functie de timestamp
    int poz = 0;
    while (poz < cereri.size() && cereri[poz]->getTimestamp() <= ts)
        poz++;

    cereri.insert(cereri.begin() + static_cast<int>(poz), move(cerereNoua));

    CerereReparatie* c = cereri[poz].get();

    // adaugam cererea la receptionerul care a inregistrat o
    int idRec = c->getIdReceptioner();
    Receptioner* r = gasesteReceptioner(idRec);
    if (r)
        r->adaugaCerere(c->getIdCerere());

}

void Service::afiseazaCereri(ostream& out) const {
    out << "Toate cererile:";
    for (int i = 0; i < cereri.size(); i++) {
        out << "\n";
        cereri[i]->afisare(out);
    }
}

//simulare service

void Service::simulare(ostream& out) {
    timpCurent++;
    out << "\n[Timp " << timpCurent << "]\n";

    if (!serviceFunctional()) {
        out << "Service-ul NU este functional (ai nevoie de minim 3 tehnicieni, 1 receptioner si 1 supervizor).\n";
    }

    // procesam cererile active
    for (int i = 0; i < cereri.size(); i++) {
        CerereReparatie* c = cereri[i].get();

        if (c->getStatus() == "ACTIVA") {
            c->procesareSec();
            int dupa = c->getDurataRamasa();

            Tehnician* t = gasesteTehnician(c->getIdTehnician());

            if (dupa > 0) {
                if (t) {
                    out << "Tehnicianul " << t->getId() << " primeste cererea cu id " << c->getIdCerere()
                        << ". Au mai ramas " << dupa << " unitati de timp.\n";
                }
            } else if (dupa == 0 && c->getStatus() == "FINALIZATA") {
                if (t) {
                    out << "Tehnicianul " << t->getId() << " finalizeaza cererea cu id " << c->getIdCerere() << ".\n";
                    
                    // adaugam valoarea reparatiei pentru bonusul la salariu
                    t->adaugaReparatie(c->getPretReparatie());
                }
            }
        }
    }

    //repartizarea cererilor in ASTEPTARE
    for (int i = 0; i < cereri.size(); i++) {
        CerereReparatie* c = cereri[i].get();
        if (c->getStatus() == "ASTEPTARE" && serviceFunctional()) {
            Tehnician* t = repartizareTehnician(*c);
            if (t) {
                c->setIdTehnician(t->getId());
                c->setStatus("ACTIVA");
                c->pornesteReparatia();

                out << "Tehnicianul " << t->getId() << " primeste cererea cu id " << c->getIdCerere() << ".\n";
            }
        }
    }

    //afisarea cererilor inca in ASTEPTARE
    out << "Cereri in asteptare: ";
    for (int i = 0; i < cereri.size(); i++) {
        CerereReparatie* c = cereri[i].get();
        if (c->getStatus() == "ASTEPTARE")
            out << c->getIdCerere() << " ";
    }

    out << "\n";
}

int Service::getTimpCurent() const {
    return timpCurent;
}