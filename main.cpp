#pragma once

#include "citiri.cpp"

// functii MENIU

void afiseazaMeniu() {
    cout << "\n MENIU PRINCIPAL \n";
    cout << "1. Gestiune angajati\n";
    cout << "2. Gestiune electrocasnice\n";
    cout << "3. Procesare cereri\n";
    cout << "0. Iesire\n";
    cout << "Alege optiunea: ";
}

void meniuGestiuneAngajati(Service& service) {
    int opt = -1;

    while (opt != 0) {
        cout << "\n GESTIUNE ANGAJATI \n";
        cout << "1. Afiseaza toti angajatii\n";
        cout << "2. Cauta angajat dupa CNP\n";
        cout << "3. Sterge angajat dupa CNP\n";
        cout << "0. Inapoi la meniul principal\n";
        cout << "Alege optiunea: ";

        cin >> opt;
        cin.ignore();

        switch (opt) {
        case 1:
            cout << "\nToti angajatii:\n";
            service.afiseazaTotiAngajatii(cout);
            break;

        case 2: {
            string cnp;
            cout << "CNP cautat: ";
            cin >> cnp;
            cin.ignore();

            cout << "\nDetalii angajat:\n";
            service.afiseazaDetaliiAngajat(cnp, cout);
            break;
        }

        case 3: {
            string cnp;
            cout << "CNP de sters: ";
            cin >> cnp;
            cin.ignore();

            bool sters = service.stergeAngajat(cnp);
            
            if (sters)
                cout << "Angajatul a fost sters.\n";
            else
                cout << "Nu exista angajat cu acest CNP.\n";
            break;
        }

        case 0:
            cout << "Revenire la meniul principal...\n";
            break;

        default:
            cout << "Optiune invalida in submeniul de angajati.\n";
            break;
        }
    }
}

void meniuGestiuneElectrocasnice(ServiceElectrocasnice& servE) {
    int opt = -1;

    while (opt != 0) {
        cout << "\n GESTIUNE ELECTROCASNICE \n";
        cout << "1. Afiseaza toate modelele reparabile\n";
        cout << "2. Adauga model reparabil manual\n";
        cout << "0. Inapoi la meniul principal\n";
        cout << "Alege optiunea: ";

        cin >> opt;
        cin.ignore();

        switch (opt) {
        case 1:
            cout << "\nModele reparabile:\n";
            servE.afisare(cout);
            break;

        case 2: {
            cout << "Tip (MasinaSpalat / Televizor / Frigider): ";
            string tip;
            cin >> tip;
            cin.ignore();

            string marca, model;
            int an;
            double pret;

            cout << "Marca: ";
            getline(cin, marca);
            cout << "Model: ";
            getline(cin, model);
            cout << "An fabricatie: ";
            cin >> an;
            cout << "Pret catalog: ";
            cin >> pret;
            cin.ignore();

            try {
                unique_ptr<Electrocasnic> e;

                if (tip == "MasinaSpalat") {
                    double cap;
                    cout << "Capacitate (kg): ";
                    cin >> cap;
                    cin.ignore();
                    e = unique_ptr<Electrocasnic>(new MasinaSpalat(marca, model, an, pret, cap));
                } else if (tip == "Televizor") {
                    double diag;
                    string unitate;
                    cout << "Diagonala: ";
                    cin >> diag;
                    cout << "Unitate (cm/inch): ";
                    cin >> unitate;
                    cin.ignore();
                    e = unique_ptr<Electrocasnic>(new Televizor(marca, model, an, pret, diag, unitate));
                } else if (tip == "Frigider") {
                    int areCong;
                    cout << "Are congelator? (1 = da, 0 = nu): ";
                    cin >> areCong;
                    cin.ignore();
                    bool b = (areCong != 0);
                    e = unique_ptr<Electrocasnic>(new Frigider(marca, model, an, pret, b));
                } else {
                    cout << "Tip necunoscut.\n";
                    break;
                }

                servE.adaugaModel(move(e));
                cout << "Model adaugat.\n";
            } catch (const exception& ex) {
                cout << "Eroare la adaugarea modelului: " << ex.what() << "\n";
            }

            break;
        }

        case 0:
            cout << "Revenire la meniul principal...\n";
            break;

        default:
            cout << "Optiune invalida in submeniul de electrocasnice.\n";
            break;
        }
    }
}

void meniuProcesareCereri(Service& service, ServiceElectrocasnice& servE, int& nrCicluri, int& cicluriRulate, bool& testIncarcat) {
    int opt = -1;

    while (opt != 0) {
        cout << "\n--- PROCESARE CERERI ---\n";
        cout << "1. Incarca date din fisier de test\n";
        cout << "2. Afiseaza toate cererile\n";
        cout << "3. Ruleaza un singur ciclu de simulare\n";
        cout << "4. Ruleaza toate ciclurile de simulare ramase\n";
        cout << "0. Inapoi la meniul principal\n";
        cout << "Alege optiunea: ";

        cin >> opt;
        cin.ignore();

        switch (opt) {
        case 1: {
            string numeFisier;
            cout << "Nume fisier test (ex: tests/test1.txt): ";
            cin >> numeFisier;
            cin.ignore();

            // resetam starea
            service = Service();
            servE = ServiceElectrocasnice();
            nrCicluri = 0;
            cicluriRulate = 0;

            bool ok = incarcareTest(numeFisier, service, servE, nrCicluri, cout);
            if (!ok) {
                cout << "Incarcarea testului a esuat.\n";
                testIncarcat = false;
            } else {
                testIncarcat = true;
                cout << "Test incarcat cu succes. Numar cicluri de simulare: "
                     << nrCicluri << "\n";
            }

            break;
        }

        case 2:
            if (!testIncarcat) {
                cout << "Nu exista date incarcate. Incarca un test mai intai.\n";
            } else {
                cout << "\n CERERI \n";
                service.afiseazaCereri(cout);
            }

            break;

        case 3:
            if (!testIncarcat) {
                cout << "Nu exista date incarcate. Incarca un test mai intai.\n";
            } else if (cicluriRulate >= nrCicluri) {
                cout << "Toate ciclurile de simulare au fost deja rulate.\n";
            } else {
                cout << "\n SIMULARE: ciclu " << (cicluriRulate + 1) << " din " << nrCicluri << "\n";
                service.simulare(cout);
                cicluriRulate++;
            }

            break;

        case 4:
            if (!testIncarcat) {
                cout << "Nu exista date incarcate. Incarca un test mai intai.\n";
            } else if (cicluriRulate >= nrCicluri) {
                cout << "Toate ciclurile de simulare au fost deja rulate.\n";
            } else {
                cout << "\n SIMULARE COMPLETA (" << (nrCicluri - cicluriRulate) << " cicluri ramase)\n";
                while (cicluriRulate < nrCicluri) {
                    service.simulare(cout);
                    cicluriRulate++;
                }
            }
            break;

        case 0:
            cout << "Revenire la meniul principal...\n";
            break;

        default:
            cout << "Optiune invalida in submeniul de cereri.\n";
            break;
        }
    }
}

int main() {
    Service service;
    ServiceElectrocasnice servE;

    int nrCicluri = 0;      // numarul total de cicluri citit din fisier
    int cicluriRulati = 0;  // cate cicluri au fost deja rulate
    bool testIncarcat = false;

    int optiune = -1;

    while (optiune != 0) {
        afiseazaMeniu();
        cin >> optiune;
        cin.ignore();

        switch (optiune) {
        case 1:
            meniuGestiuneAngajati(service);
            break;
        case 2:
            meniuGestiuneElectrocasnice(servE);
            break;
        case 3:
            meniuProcesareCereri(service, servE, nrCicluri, cicluriRulati, testIncarcat);
            break;
        case 0:
            cout << "Iesire...\n";
            break;
        default:
            cout << "Optiune invalida in meniul principal.\n";
            break;
        }
    }

    return 0;
}