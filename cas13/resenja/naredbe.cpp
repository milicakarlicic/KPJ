#include "naredbe.hpp"

map<string, int> promenljive;

//////////////////////////////////////////////////////////////////////

void IspisS::Izvrsi() const {
    cout << _String << endl;
}

void IspisE::Izvrsi() const {
    cout << _Izraz->Izracunaj() << endl;
}

IspisE::~IspisE() {
    delete _Izraz;
}

void Blok::Izvrsi()const {
    for(auto& pom : _Naredbe)
        pom->Izvrsi();
}

Blok::~Blok() {
    for(auto& pom : _Naredbe)
        delete pom;
}

Dodjela::~Dodjela() {
    delete _Izraz;
}

void Dodjela::Izvrsi() const {
    promenljive[_Id] = _Izraz->Izracunaj();
}

void Unesi::Izvrsi() const {
    int vr;
    cin >> vr;
    promenljive[_Id] = vr;
}

UslovSaInace::~UslovSaInace() {
    delete _Izraz;
    delete _N1;
    delete _N2;
}

void UslovSaInace::Izvrsi() const {
    if(_Izraz->Izracunaj())
        _N1->Izvrsi();
    else
        _N2->Izvrsi();
}

UslovBezInace::~UslovBezInace() {
    delete _Izraz;
    delete _N;
}

void UslovBezInace::Izvrsi() const {
    if(_Izraz->Izracunaj())
        _N->Izvrsi();
}

Petlja::~Petlja() {
    delete _Izraz;
    delete _Naredba;
}

void Petlja::Izvrsi() const {
    while(_Izraz->Izracunaj())
        _Naredba->Izvrsi();
}

