#pragma once

#include "electrocasnic.h"
#include <vector>
#include <memory>

class ServiceElectrocasnice {
private:
    vector<unique_ptr<Electrocasnic>> modele;

public:
    ServiceElectrocasnice() = default;

    // adauga un model reparabil
    void adaugaModel(unique_ptr<Electrocasnic> e);

    // sterge un model dupa tip + marca + model
    void stergeModel(const Electrocasnic& e);

    bool esteReparabil(const Electrocasnic& e) const;

    void afisare(ostream& out) const;
};