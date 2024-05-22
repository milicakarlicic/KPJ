#include "polinomi.hpp"

Polinom::Polinom(const vector<double>& koef, unsigned stepen)
    : _Koef(koef), _Stepen(stepen) {}

Polinom Polinom::operator +(const Polinom& p) const {
    unsigned stepen = max(_Stepen, p._Stepen);
    vector<double> rezultat(stepen + 1);
    unsigned i;

    for(i = 0; i <= _Stepen && i <= p._Stepen; i++)
        rezultat[i] = _Koef[i] + p._Koef[i];

    for(; i <= _Stepen; i++)
        rezultat[i] = _Koef[i];

    for(; i <= p._Stepen; i++)
        rezultat[i] = p._Koef[i];

    return Polinom(rezultat, stepen);
}

Polinom Polinom::operator -(const Polinom& p) const {
    unsigned stepen = max(_Stepen, p._Stepen);
    vector<double> rezultat(stepen + 1);
    unsigned i;

    for(i = 0; i <= _Stepen && i <= p._Stepen; i++)
        rezultat[i] = _Koef[i] - p._Koef[i];

    for(; i <= _Stepen; i++)
        rezultat[i] = _Koef[i];

    for(; i <= p._Stepen; i++)
        rezultat[i] = - p._Koef[i];

    return Polinom(rezultat, stepen);
}

Polinom Polinom::operator *(const Polinom& p) const {
    unsigned stepen = _Stepen + p._Stepen;
    vector<double> rezultat(stepen + 1, 0);

    for(unsigned i = 0; i <= _Stepen; i++)
        for(unsigned j = 0; j <= p._Stepen; j++)
            rezultat[i + j] += _Koef[i] * p._Koef[j];

    return Polinom(rezultat, stepen);
}

Polinom Polinom::operator -() const {
    vector<double> rezultat(_Stepen + 1);

    for(unsigned i = 0; i <= _Stepen; i++)
        rezultat[i] = - _Koef[i];

    return Polinom(rezultat, _Stepen);
}

void Polinom::Ispisi() const {
    unsigned i = 0;

    if(_Stepen == 0 && _Koef[0] == 0) {
        cout << "0" << endl;
        return;
    }

    while(_Koef[i] == 0)
        i++;

    if(i == 0) {
            string znak = _Koef[i] > 0 ? "" : "- ";
            cout << znak << abs(_Koef[i]);
    } else if(i == 1) {
        if(_Koef[i] == 1)
            cout << "x";
        else if(_Koef[i] == -1)
            cout << "- x";
        else {
            string znak = _Koef[i] > 0 ? "" : "- ";
            cout << znak << abs(_Koef[i]) << "x";
        }
    } else {
        if(_Koef[i] == 1)
            cout << "x^" << i;
        else if(_Koef[i] == -1)
            cout << "- x^" << i;
        else {
            string znak = _Koef[i] > 0 ? "" : "- ";
            cout << znak << abs(_Koef[i]) << "x^" << i;
        }
    }

    i++;
    for(; i < _Koef.size(); i++) {
        if(_Koef[i] == 0)
            continue;
        string znak = _Koef[i] > 0 ? " + " : " - ";
        if(i == 0)
            cout << _Koef[i];
        else if(i == 1) {
            if(_Koef[i] == 1 || _Koef[i] == -1)
                cout << znak << "x";
            else
                cout << znak << abs(_Koef[i]) << "x";
        }
        else {
            if(_Koef[i] == 1 || _Koef[i] == -1)
                cout << znak << "x^" << i;
            else
                cout << znak << abs(_Koef[i]) << "x^" << i;
        }
    }

    cout << endl;
}

bool Polinom::operator ==(const Polinom& p) const {
    if(_Stepen != p._Stepen)
        return false;

    for(unsigned i = 0; i <= _Stepen; i++)
        if(_Koef[i] != p._Koef[i])
            return false;

    return true;
}

bool Polinom::operator !=(const Polinom& p) const {
    if(_Stepen != p._Stepen)
        return true;

    for(unsigned i = 0; i <= _Stepen; i++)
        if(_Koef[i] != p._Koef[i])
            return true;

    return false;
}

Polinom Polinom::Izvod() const {
    // npr. <1>' --> <0>
    if(_Stepen == 0) {
        vector<double> rezultat;
        rezultat.push_back(0);
        return Polinom(rezultat, 0);
    }

    unsigned stepen = _Stepen - 1;
    vector<double> rezultat(stepen + 1);

    for(unsigned i = 1; i <= _Stepen; i++)
        rezultat[i - 1] = _Koef[i] * i;

    return Polinom(rezultat, stepen);
}

Polinom Polinom::Integral(double d) const {
    unsigned stepen = _Stepen + 1;
    vector<double> rezultat(stepen + 1);
    rezultat[0] = d;

    for(unsigned i = 0; i <= _Stepen; i++)
        rezultat[i + 1] = _Koef[i]/(i + 1);

    return Polinom(rezultat, stepen);
}

double Polinom::operator [](double x) const {
    double rezultat = 0;

    for(unsigned i = _Stepen; i > 0; i--) {
        rezultat += _Koef[i];
        rezultat *= x;
    }

    rezultat += _Koef[0];

    return rezultat;
}
