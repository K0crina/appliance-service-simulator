#pragma once

#include "electrocasnice/electrocasnic.h"
#include <memory>
#include <ctime>

class CerereReparatie {
private:
    int idCerere;    
    unique_ptr<Electrocasnic> eco;

    time_t timestamp;                // data + ora depunerii

    int complexitate;                // 1...5; 0 daca nu poate fi reparat
    int durataEstimata;              // vechime * complexitate
    double pretReparatie;            // pretCatalog * durataEstimata

    int durataRamasa;
    string status;                   // "ASTEPTARE", "ACTIVA" SAU "FINALIZATA"

    int idReceptioner;               // cine a inregistrat cererea
    int idTehnician;                 // cui e alocata (-1 daca nu e alocata)

    static int anCurent();
    void calculeaza();             // calculeaza durataEstimata si pretReparatie

public:
    CerereReparatie();
    CerereReparatie(int idCerere, unique_ptr<Electrocasnic> eco, time_t timestamp, int complexitate, int idReceptioner);
                    
    // getteri
    int getIdCerere() const;

    const Electrocasnic* getElectrocasnic() const;    // null daca nu e reparabil

    time_t getTimestamp() const;
    int getComplexitate() const;
    int getDurataEstimata() const;
    double getPretReparatie() const;

    int getDurataRamasa() const;
    string getStatus() const;

    int getIdReceptioner() const;
    int getIdTehnician() const;

    // seteri
    void setStatus(const string& s);
    void setIdTehnician(int idTeh);

    // Format asteptat: "ZZ.LL.AAAA HH:MM:SS"
    static time_t dataDepunere(const string& s);

    // cand cererea devine activa, durataRamasa incepe de la durataEstimata
    void pornesteReparatia();

    // daca e ACTIVA, scade durataRamasa => cand ajunge la 0, setam statusul la FINALIZATA
    void procesareSec();

    void afisare(ostream& out) const;
    friend ostream& operator<<(ostream& out, const CerereReparatie& c);

};
