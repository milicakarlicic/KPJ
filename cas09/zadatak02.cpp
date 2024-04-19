#include <iostream>
#include <cstdlib>

// u okviru kartice dodatna literatura: C++ kroz primjere, klasa Razlomak...

using namespace std;

class Razlomak {
  public:
    explicit Razlomak(int brojilac = 0, int imenilac = 1)
        : _Brojilac(brojilac), _Imenilac(imenilac) {}

    int VratiBrojilac() const {
        return _Brojilac;
    }

    int VratiImenilac() const {
        return _Imenilac;
    }

    Razlomak operator +(const Razlomak& r) const {
        return Razlomak(_Brojilac * r._Imenilac + r._Brojilac * _Imenilac, _Imenilac * r._Imenilac);
    }

    Razlomak operator -(const Razlomak& r) const {
        return Razlomak(_Brojilac * r._Imenilac - r._Brojilac * _Imenilac, _Imenilac * r._Imenilac);
    }

    Razlomak operator *(const Razlomak& r) const {
        return Razlomak(_Brojilac * r._Brojilac, _Imenilac * r._Imenilac);
    }

    Razlomak operator /(const Razlomak& r) const {
        return Razlomak(_Brojilac * r._Imenilac, _Imenilac * r._Brojilac);
    }

    // postfiksni operator inkrementiranja
    // zasto ne mozemo da vratimo referencu?
    Razlomak operator ++(int) {
        Razlomak r = Razlomak(_Brojilac, _Imenilac);
        _Brojilac += _Imenilac;

        return r;
    }

    // prefiksni operator inkrementiranja
    Razlomak& operator ++() {
        _Brojilac += _Imenilac;

        return *this;
    }

    operator double() {
        return 1.0 * _Brojilac / _Imenilac;
    }

  private:
    int _Brojilac;
    int _Imenilac;
};

// zasto se operatori ispisa/upisa definisu van klase?

ostream& operator <<(ostream& izlaz, const Razlomak& r) {
    izlaz << r.VratiBrojilac() << "/" << r.VratiImenilac();
    return izlaz;
}

istream& operator >>(istream& ulaz, Razlomak& r) {
    int brojilac, imenilac;
    char c;

    ulaz >> brojilac >> c >> imenilac;
    if(c != '/') {
    cerr << "Ocekivan /" << endl;
    exit(EXIT_FAILURE);
    }

    r = Razlomak(brojilac, imenilac);

    return ulaz;
}

int main() {
    Razlomak r1(1, 4);

    cout << r1 + 2 << endl;

    return 0;
}
