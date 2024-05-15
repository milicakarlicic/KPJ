#ifndef POLINOMI_HPP
#define POLINOMI_HPP

// U zaglavlju pisemo potpise metode i implementacije nekih veoma jednostavnih metoda

#include <iostream>
#include <vector>

using namespace std;

class Polinom {
public:
    Polinom() {}
    Polinom(const vector<double> &koef, unsigned stepen)
        : _Koef(koef), _Stepen(stepen) {}

    void Ispisi() const;
    Polinom operator + (const Polinom &p) const;
    Polinom operator - (const Polinom &p) const;
    Polinom operator * (const Polinom &p) const;
    Polinom operator - () const;
private:
    vector<double> _Koef;
    unsigned _Stepen;
};

ostream& operator << (ostream &izlaz, const Polinom &p);

#endif
