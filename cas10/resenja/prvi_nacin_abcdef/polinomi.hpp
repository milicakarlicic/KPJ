#ifndef POLINOMI_HPP
#define POLINOMI_HPP

#include <iostream>
#include <vector>

using namespace std;

class Polinom {
public:
    // jednostavne implementacije mogu u zaglavlju
    Polinom() {}
    Polinom(const vector<double>& koef, unsigned stepen);
    void Ispisi() const;
    Polinom operator +(const Polinom& p) const;
    Polinom operator -(const Polinom& p) const;
    Polinom operator *(const Polinom& p) const;
    Polinom operator -() const;
    bool operator ==(const Polinom& p) const;
    bool operator !=(const Polinom& p) const;
    double operator [](double d) const;
    Polinom Izvod() const;
    Polinom Integral(double d) const;

private:
    vector<double> _Koef;
    unsigned _Stepen;
};

#endif
