#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>
#include <cctype>
#include <ctime>
#include <cstring>
using namespace std;

// verifica formatul si extrage z, l, a din "ZZ.LL.AAA"
void data(const string& s, int& z, int& l, int& a);

// ia data curenta din sistem
void dataCurenta(int& z, int& l, int& a);

// calculeaza vechimea in ani intregi (de la data angajarii pana azi)
int vechime(const string& dA);