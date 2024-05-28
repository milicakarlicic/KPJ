#include "izrazi.hpp"

extern map<string, int> promenljive;

//////////////////////////////////////////////////////////////////////

int Konstanta::Izracunaj() const {
    return _Vrednost;
}

Izraz* Konstanta::Kopija() const {
    return new Konstanta(_Vrednost);
}

//////////////////////////////////////////////////////////////////////

int Promenljiva::Izracunaj() const {
    return promenljive[_Naziv];
}

Izraz* Promenljiva::Kopija() const {
    return new Promenljiva(_Naziv);
}

//////////////////////////////////////////////////////////////////////

UnarniIzraz::~UnarniIzraz() {
    delete _Argument;
}

int Sinus::Izracunaj() const {
    return sin(_Argument->Izracunaj());
}

Izraz* Sinus::Kopija() const {
    return new Sinus(_Argument->Kopija());
}

int Kosinus::Izracunaj() const {
    return cos(_Argument->Izracunaj());
}

Izraz* Kosinus::Kopija() const {
    return new Kosinus(_Argument->Kopija());
}

//////////////////////////////////////////////////////////////////////

BinarniIzraz::~BinarniIzraz() {
    delete _Levi;
    delete _Desni;
}

int Zbir::Izracunaj() const {
    return _Levi->Izracunaj() + _Desni->Izracunaj();
}

Izraz* Zbir::Kopija() const {
    return new Zbir(_Levi->Kopija(), _Desni->Kopija());
}

int Proizvod::Izracunaj() const {
    return _Levi->Izracunaj() * _Desni->Izracunaj();
}

Izraz* Proizvod::Kopija() const {
    return new Proizvod(_Levi->Kopija(), _Desni->Kopija());
}

int Mod::Izracunaj() const {
    return _Levi->Izracunaj() % _Desni->Izracunaj();
}

Izraz* Mod::Kopija() const {
    return new Mod(_Levi->Kopija(), _Desni->Kopija());
}

int Vece::Izracunaj() const {
    return _Levi->Izracunaj() > _Desni->Izracunaj();
}

Izraz* Vece::Kopija() const {
    return new Vece(_Levi->Kopija(), _Desni->Kopija());
}

int Manje::Izracunaj() const {
    return _Levi->Izracunaj() < _Desni->Izracunaj();
}

Izraz* Manje::Kopija() const {
    return new Manje(_Levi->Kopija(), _Desni->Kopija());
}
