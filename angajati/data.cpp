#include "data.h"

bool numere(const string& s) {
    for (int i = 0; i < s.length(); i++)
        if (!isdigit(s[i]))
            return false;

    return true;
}



void data(const string& s, int& z, int& l, int& a) {
    if (s.size() != 10 || s[2] != '.' || s[5] != '.')
        throw invalid_argument("Data invalida: format corect = ZZ.LL.AAAA.");

    string zi = s.substr(0,2);
    string luna = s.substr(3,2);
    string an = s.substr(6,4);    

    if (!numere(zi) || !numere(luna) || !numere(an))
        throw invalid_argument("Data invalida: contine caractere non-cifra.");

    z = stoi(zi);
    l = stoi(luna);
    a = stoi(an);

    if (z < 1 || z > 31)
        throw invalid_argument("Zi invalida in data.");

    if (l < 1 || l > 12)
        throw invalid_argument("Luna invalida in data.");

    int anCurent;
    time_t tt = time(nullptr);
    tm* t = localtime(&tt);
    anCurent = t->tm_year + 1900;

    if (a < 1950|| a > anCurent)
        throw invalid_argument("An invalid in data.");
}

void dataCurenta(int& z, int& l, int& a) {
    chrono::system_clock::time_point now = chrono::system_clock::now();
    time_t tt = chrono::system_clock::to_time_t(now);
    tm* t = localtime(&tt);

    z = t->tm_mday;
    l = t->tm_mon + 1;
    a = t->tm_year + 1900;
}

int vechime(const string& dA) {
    int zA, lA, aA;
    data(dA, zA, lA, aA);

    int zC, lC, aC;
    dataCurenta(zC, lC, aC);

    int vechime = aC - aA;

    // daca anul asta nu a trecut inca data (luna/zi), scadem 1
    if (lC < lA || (lC == lA && zC < zA))
        vechime--;

    if (vechime < 0) vechime = 0;
    return vechime;
}