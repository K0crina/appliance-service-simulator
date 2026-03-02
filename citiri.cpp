#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

#include "service.h"
#include "electrocasnice/serviceElectrocasnice.h"
#include "angajati/receptioner.h"
#include "angajati/tehnician.h"
#include "angajati/supervizor.h"
#include "electrocasnice/masinaSpalat.h"
#include "electrocasnice/televizor.h"
#include "electrocasnice/frigider.h"
#include "cerereReparatie.h"

//parsare din fisierul test
vector<string> parsare(const string& line, char sep) {
    vector<string> parts;
    string cur = "";

    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == sep) {
            parts.push_back(cur);
            cur.clear();
        } else
            cur.push_back(line[i]);
    }

    parts.push_back(cur);

    return parts;
}

//incarcare angajati
void incarcaAngajati(Service& service, const vector<string>& linii, int start, int end, ostream& outErori) {
    for (int i = start; i <= end; i++) {
        string linie = linii[i];
        if (linie.size() == 0) continue;

        vector<string> p = parsare(linie, ';');

        if ((int)p.size() != 7) {
            outErori << "Eroare la citire: Angajat invalid pe linia " << (i + 1) << ", cauza: numar gresit de campuri.\n";
            continue;
        }

        string tip = p[0];
        string idStr = p[1];
        string nume = p[2];
        string prenume = p[3];
        string cnpStr = p[4];
        string dataAng   = p[5];
        string domiciliu = p[6];

        int id;
        try {
            id = stoi(idStr);
        } catch (...) {
            outErori << "Eroare la citire: Angajat invalid pe linia " << (i + 1) << ", cauza: ID invalid (" << idStr << ").\n";
            continue;
        }

        try {
            unique_ptr<Angajat> a;

            if (tip == "RECEPTIONER") {
                a = unique_ptr<Angajat>(new Receptioner(id, nume, prenume, cnpStr.c_str(), dataAng, domiciliu));
            } else if (tip == "TEHNICIAN") {
                a = unique_ptr<Angajat>(new Tehnician(id, nume, prenume, cnpStr.c_str(), dataAng, domiciliu));
            } else if (tip == "SUPERVIZOR") {
                a = unique_ptr<Angajat>(new Supervizor(id, nume, prenume, cnpStr.c_str(), dataAng, domiciliu));
            } else {
                outErori << "Eroare la citire: Angajat invalid pe linia "
                         << (i + 1) << ", cauza: tip necunoscut (" << tip << ").\n";
                continue;
            }

            service.adaugaAngajat(move(a));
        } catch (const exception& ex) {
            outErori << "Eroare la citire: Angajat invalid pe linia " << (i + 1) << ", cauza: " << ex.what() << "\n";
        }
    }
}

//incarcare specializari
void incarcaSpecializari(Service& service, const vector<string>& linii, int start, int end, ostream& outErori) {
    for (int i = start; i <= end; i++) {
        string linie = linii[i];
        if (linie.size() == 0) continue;

        vector<string> p = parsare(linie, ';');
        if ((int)p.size() != 3) {
            outErori << "Eroare la citire: Specializare invalida pe linia " << (i + 1) << ", cauza: numar gresit de campuri.\n";
            continue;
        }

        string idStr = p[0];
        string tip = p[1];
        string marca = p[2];

        int id;
        try {
            id = stoi(idStr);
        } catch (...) {
            outErori << "Eroare la citire: Specializare invalida pe linia " << (i + 1) << ", cauza: ID tehnician invalid (" << idStr << ").\n";
            continue;
        }

        Tehnician* t = service.gasesteTehnician(id);
        if (!t) {
            outErori << "Eroare la citire: Specializare invalida pe linia "
                    << (i + 1) << ", cauza: tehnician inexistent (" << id << ").\n";
            continue;
        }
        t->adaugaSpecializare(tip, marca);
    }
}

//incarcare modele
unique_ptr<Electrocasnic> creeazaModel(const vector<string>& p) {
    string tip = p[0];
    string marca = p[1];
    string model = p[2];

    int an;
    double pret;

    an = stoi(p[3]);
    pret = stod(p[4]);

    if (tip == "MasinaSpalat") {
        if ((int)p.size() < 6)
            throw invalid_argument("Lipseste capacitatea pentru MasinaSpalat.");
        double cap = stod(p[5]);
        return unique_ptr<Electrocasnic>(new MasinaSpalat(marca, model, an, pret, cap));
    } else if (tip == "Televizor") {
        if ((int)p.size() < 7)
            throw invalid_argument("Lipsesc campuri pentru Televizor (diagonala, unitate).");
        double diag = stod(p[5]);
        string unitate = p[6];
        return unique_ptr<Electrocasnic>(new Televizor(marca, model, an, pret, diag, unitate));
    } else if (tip == "Frigider") {
        if ((int)p.size() < 6)
            throw invalid_argument("Lipseste campul areCongelator pentru Frigider.");
        int v = stoi(p[5]);
        bool areCong = (v != 0);
        return unique_ptr<Electrocasnic>(new Frigider(marca, model, an, pret, areCong));
    } else {
        throw invalid_argument("Tip electrocasnic necunoscut (" + tip + ").");
    }
}

void incarcaModele(ServiceElectrocasnice& servE, const vector<string>& linii, int start, int end, ostream& outErori) {
    for (int i = start; i <= end; i++) {
        string linie = linii[i];
        if (linie.size() == 0) continue;

        vector<string> p = parsare(linie, ';');
        if ((int)p.size() < 5) {
            outErori << "Eroare la citire: Model invalid pe linia " << (i + 1) << ", cauza: numar gresit de campuri.\n";
            continue;
        }

        try {
            unique_ptr<Electrocasnic> e = creeazaModel(p);
            servE.adaugaModel(move(e));
        } catch (const exception& ex) {
            outErori << "Eroare la citire: Model invalid pe linia " << (i + 1) << ", cauza: " << ex.what() << "\n";
        }
    }
}

//incarcare modele
void incarcaCereri(Service& service, ServiceElectrocasnice& servE, const vector<string>& linii, int start, int end, ostream& outErori) {
    for (int i = start; i <= end; i++) {
        string linie = linii[i];
        if (linie.empty())
            continue;

        vector<string> p = parsare(linie, ';');
        if ((int)p.size() != 9) {
            outErori << "Eroare la citire: Cerere invalida pe linia " << (i + 1) << ", cauza: numar gresit de campuri.\n";
            continue;
        }

        string idStr = p[0];
        string tsStr = p[1];
        string tip = p[2];
        string marca = p[3];
        string model = p[4];
        string anStr = p[5];
        string pretStr = p[6];
        string compStr = p[7];
        string idRecStr = p[8];

        int idCer, an, comp, idRec;
        double pret;

        try { 
            idCer = stoi(idStr); 
        } catch (...) {
            outErori << "Eroare la citire: Cerere invalida pe linia " << (i + 1) << ", cauza: ID invalid (" << idStr << ").\n";
            continue;
        }
        try { 
            an = stoi(anStr); 
        } catch (...) {
            outErori << "Eroare la citire: Cerere invalida pe linia " << (i + 1) << ", cauza: an invalid (" << anStr << ").\n";
            continue;
        }
        try { 
            pret = stod(pretStr); 
        } catch (...) {
            outErori << "Eroare la citire: Cerere invalida pe linia " << (i + 1) << ", cauza: pret invalid (" << pretStr << ").\n";
            continue;
        }
        try { 
            comp = stoi(compStr); 
        } catch (...) {
            outErori << "Eroare la citire: Cerere invalida pe linia " << (i + 1) << ", cauza: complexitate invalida (" << compStr << ").\n";
            continue;
        }
        try { 
            idRec = stoi(idRecStr);
        } catch (...) {
            outErori << "Eroare la citire: Cerere invalida pe linia " << (i + 1) << ", cauza: ID receptioner invalid (" << idRecStr << ").\n";
            continue;
        }

        try {
            time_t ts = CerereReparatie::dataDepunere(tsStr);

            unique_ptr<Electrocasnic> eco(new Electrocasnic(tip, marca, model, an, pret));

            bool reparabil = servE.esteReparabil(*eco);

            unique_ptr<CerereReparatie> c;

            // daca complexitatea este 0 sau modelul nu este reparabil  => cererea devine NEREPARABIL
            if (comp == 0 || !reparabil)
                c = unique_ptr<CerereReparatie>(new CerereReparatie(idCer, unique_ptr<Electrocasnic>(), ts, comp, idRec));
            else {
                c = unique_ptr<CerereReparatie>(new CerereReparatie(idCer,move(eco), ts, comp, idRec));
            }

            // adaugam cererea in service
            service.adaugaCerere(move(c));
            
        } catch (const exception& ex) {
            outErori << "Eroare la citire: Cerere invalida pe linia " << (i + 1) << ", cauza: " << ex.what() << "\n";
        }
    }
}

//numarul de cicluri
int citireCicluri(const vector<string>& linii, int start, int end, ostream& outErori) {
    for (int i = start; i <= end; i++) {
        string linie = linii[i];
        if (linie.size() == 0) continue;

        try {
            int nr = stoi(linie);
            if (nr <= 0) {
                outErori << "Eroare la citire: numar de cicluri invalid pe linia " << (i + 1) << " (" << linie << "). Se face un ciclu.\n";
                return 1;
            }
            return nr;
        } catch (...) {
            outErori << "Eroare la citire: nu pot citi numarul de cicluri de pe linia " << (i + 1) << " (" << linie << "). Se face un ciclu.\n";
            return 1;
        }
    }

    outErori << "Eroare la citire: lipseste blocul de simulare, folosesc 1 ciclu.\n";
    return 1;
}

//incarcare test complet
bool incarcareTest(const string& numeFisier, Service& service, ServiceElectrocasnice& servE, int& nrCicluri, ostream& outErori) {
    ifstream f(numeFisier.c_str());
    if (!f.is_open()) {
        outErori << "Nu s-a putut deschide fisierul: " << numeFisier << "\n";
        return false;
    }

    vector<string> linii;
    string linie;

    while (getline(f, linie))
        linii.push_back(linie);

    // cautam liniile goale care separa blocurile
    vector<int> delim;
    for (int i = 0; i < (int)linii.size(); i++)
        if (linii[i].size() == 0)
            delim.push_back(i);

    if ((int)delim.size() < 4) {
        outErori << "Fisier test invalid: trebuie sa aiba 5 blocuri separate prin linii goale.\n";
        return false;
    }

    int startAng = 0;
    int endAng = delim[0] - 1;

    int startSpec = delim[0] + 1;
    int endSpec = delim[1] - 1;

    int startMod = delim[1] + 1;
    int endMod = delim[2] - 1;

    int startCer = delim[2] + 1;
    int endCer = delim[3] - 1;

    int startSim = delim[3] + 1;
    int endSim = (int)linii.size() - 1;

    // incarcam fiecare bloc
    incarcaAngajati(service, linii, startAng, endAng, outErori);
    incarcaSpecializari(service, linii, startSpec, endSpec, outErori);
    incarcaModele(servE, linii, startMod, endMod, outErori);
    incarcaCereri(service, servE, linii, startCer, endCer, outErori);
    nrCicluri = citireCicluri(linii, startSim, endSim, outErori);

    return true;
}