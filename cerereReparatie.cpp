#include "cerereReparatie.h"
#include <stdexcept>
#include <iomanip>

int CerereReparatie::anCurent() {
    time_t t = time(nullptr);
    tm* x = localtime(&t);
    return x->tm_year + 1900;
}

void CerereReparatie::calculeaza() {
    int vech = anCurent() - eco->getAnFabricatie();
    if (vech < 0) vech = 0;

    durataEstimata = vech * complexitate;
    pretReparatie = eco->getPretCatalog() * (double)durataEstimata;
}

time_t CerereReparatie::dataDepunere(const string& s) {
    if ((int)s.size() != 19)
        throw invalid_argument("Timestamp invalid: format corect ZZ.LL.AAAA HH:MM:SS");

    if (s[2] != '.' || s[5] != '.' || s[10] != ' ' || s[13] != ':' || s[16] != ':')
        throw invalid_argument("Timestamp invalid: separatoare gresite");

    int idxs[] = {0,1,3,4,6,7,8,9,11,12,14,15,17,18}; // pozitii ce trebuie verificate
    for (int i = 0; i < 14; i++) {
        if (!isdigit((unsigned char)s[idxs[i]]))
            throw invalid_argument("Timestamp invalid: contine caractere non-cifre");
    }

    int zi   = (s[0]-'0')*10 + (s[1]-'0');
    int luna = (s[3]-'0')*10 + (s[4]-'0');
    int an   = (s[6]-'0')*1000 + (s[7]-'0')*100 + (s[8]-'0')*10 + (s[9]-'0');

    int ora  = (s[11]-'0')*10 + (s[12]-'0');
    int min  = (s[14]-'0')*10 + (s[15]-'0');
    int sec  = (s[17]-'0')*10 + (s[18]-'0');

    tm t{};
    t.tm_mday = zi;
    t.tm_mon  = luna - 1;
    t.tm_year = an - 1900;
    t.tm_hour = ora;
    t.tm_min  = min;
    t.tm_sec  = sec;
    t.tm_isdst = -1;

    time_t res = mktime(&t);
    if (res == (time_t)-1)
        throw invalid_argument("Timestamp invalid: nu se poate converti");

    return res;
}

CerereReparatie::CerereReparatie(): idCerere(0), eco(nullptr), timestamp(0), complexitate(0),
      durataEstimata(0), pretReparatie(0.0), durataRamasa(0), status("ASTEPTARE"), idReceptioner(-1), idTehnician(-1) {}

CerereReparatie::CerereReparatie(int idC, unique_ptr<Electrocasnic> e, time_t ts, int comp, int idRec)
    : idCerere(idC), eco(move(e)), timestamp(ts), complexitate(comp), durataEstimata(0),
      pretReparatie(0.0), durataRamasa(0), status("ASTEPTARE"), idReceptioner(idRec), idTehnician(-1) {
    
    if (idCerere <= 0)
        throw invalid_argument("ID cerere invalid: trebuie > 0.");

    if (idReceptioner <= 0)
        throw invalid_argument("ID receptioner pentru cerere invalid: trebuie > 0.");

    if (!eco) {
        complexitate = 0;
        durataEstimata = 0;
        pretReparatie = 0.0;
        durataRamasa = 0;
        status = "NEREPARABIL";
        return;
    }

    if (complexitate < 1 || complexitate > 5)
        throw invalid_argument("Complexitate invalida: trebuie de la 1 la 5.");

    calculeaza();
}

//getteri
int CerereReparatie::getIdCerere() const { 
    return idCerere;
}

time_t CerereReparatie::getTimestamp() const { 
    return timestamp; 
}

int CerereReparatie::getComplexitate() const { 
    return complexitate; 
}

int CerereReparatie::getDurataEstimata() const { 
    return durataEstimata; 
}

double CerereReparatie::getPretReparatie() const { 
    return pretReparatie; 
}

int CerereReparatie::getDurataRamasa() const { 
    return durataRamasa; 
}

string CerereReparatie::getStatus() const { 
    return status; 
}

int CerereReparatie::getIdReceptioner() const { 
    return idReceptioner; 
}

int CerereReparatie::getIdTehnician() const { 
    return idTehnician; 
}

const Electrocasnic* CerereReparatie::getElectrocasnic() const {
    return eco.get();
}

//seteri
void CerereReparatie::setIdTehnician(int idTech) {
    idTehnician = idTech;
}

void CerereReparatie::setStatus(const string& s) {
    status = s;
}

//pornire reparatie
void CerereReparatie::pornesteReparatia() {
    if (status == "NEREPARABIL")
        return;

    status = "ACTIVA";
    durataRamasa = durataEstimata;
}

void CerereReparatie::procesareSec() {
    if (status != "ACTIVA")
        return;

    if (durataRamasa > 0)
        durataRamasa--;

    if (durataRamasa == 0)
        status = "FINALIZATA";
}

void CerereReparatie::afisare(ostream& out) const {
    out << "Cerere Reparatie \n";
    out << "ID cerere: " << idCerere << "\n";

    out << "Electrocasnic: \n";
    if (eco)
        out << *eco;
    else
        out << "Nu poate fi reparat!\n";

    // afisare timestamp: ZZ.LL.AAAA HH:MM:SS
    tm* t = localtime(&timestamp);
    out << "Depusa la: "
        << setw(2) << setfill('0') << t->tm_mday << "."
        << setw(2) << setfill('0') << (t->tm_mon + 1) << "."
        << (t->tm_year + 1900) << " "
        << setw(2) << setfill('0') << t->tm_hour << ":"
        << setw(2) << setfill('0') << t->tm_min << ":"
        << setw(2) << setfill('0') << t->tm_sec << "\n";

    out << "Status: " << status << "\n";

    out << "ID Receptioner: " << idReceptioner << "\n";
    out << "ID Tehnician: " << idTehnician << "\n";

    out << "Complexitate: " << complexitate << "\n";
    out << "Durata estimata: " << durataEstimata << "\n";
    out << "Pret reparatie: " << pretReparatie << "\n";
    out << "Durata ramasa: " << durataRamasa << "\n";
}

ostream& operator<<(ostream& out, const CerereReparatie& c) {
    c.afisare(out);
    return out;
}

