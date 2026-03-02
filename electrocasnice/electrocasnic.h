#pragma once

#include <iostream>
#include <string>

using namespace std;

class Electrocasnic {
protected:
    string tip;
    string marca;
    string model;
    int anFabricatie;
    double pretCatalog;

public:
    Electrocasnic();
    Electrocasnic(const string& tip,
                  const string& marca,
                  const string& model,
                  int anFabricatie,
                  double pretCatalog);

    virtual ~Electrocasnic() = default;

    // getteri
    string getTip() const;
    string getMarca() const;
    string getModel() const;
    int getAnFabricatie() const;
    double getPretCatalog() const;

    // afisare
    virtual void afisare(ostream& out) const;
    friend ostream& operator<<(ostream& out, const Electrocasnic& e);
};