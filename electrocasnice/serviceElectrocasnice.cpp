#include "serviceElectrocasnice.h"

void ServiceElectrocasnice::adaugaModel(unique_ptr<Electrocasnic> e) {
    /*
    if (!e)
        return;
    */

    // verificam daca deja exista
    for (int i = 0; i < (int)modele.size(); i++)
        if (modele[i]->getTip() == e->getTip() && modele[i]->getMarca() == e->getMarca() && modele[i]->getModel() == e->getModel())
            return;

    modele.push_back(move(e));
}

void ServiceElectrocasnice::stergeModel(const Electrocasnic& e) {
    for (int i = 0; i < (int)modele.size(); i++)
        if (modele[i]->getTip() == e.getTip() && modele[i]->getMarca() == e.getMarca() && modele[i]->getModel() == e.getModel()) {
            modele.erase(modele.begin() + i);
            return;
        }
}

bool ServiceElectrocasnice::esteReparabil(const Electrocasnic& e) const {
    for (int i = 0; i < (int)modele.size(); i++)
        if (modele[i]->getTip() == e.getTip() && modele[i]->getMarca() == e.getMarca() && modele[i]->getModel() == e.getModel())
            return true;

    return false;
}

void ServiceElectrocasnice::afisare(ostream& out) const {
    if (modele.empty()) {
        out << "\n";
        return;
    }

    for (int i = 0; i < (int)modele.size(); i++) {
        out << *modele[i] << "\n";
    }
}
