#include "funkcije.hpp"

map<char, double> promenljive;

//////////////////////////////////////////////////////////////////////

Funkcija::~Funkcija() {
        delete _Izraz;
}

bool Funkcija::Provera() const {
    return _Izraz->Provera(_Arg);
}

void Funkcija::Ispis() const {
    _Izraz->Ispis();
    cout << endl;
}

double Funkcija::operator [](const vector<double>& arg) const {
    if(arg.size() != _Arg.size())
        throw "Neodgovarajuci broj argumenata funkcije.";

    for(unsigned i = 0; i < _Arg.size(); i++)
        promenljive[_Arg[i]] = arg[i];
    return _Izraz->Izracunaj();
}

Funkcija* Funkcija::Izvod(char x) const {
    return new Funkcija(_Arg, _Izraz->Izvod(x));
}

//////////////////////////////////////////////////////////////////////

bool Konstanta::Provera(const vector<char>& arg) const {
    NEBITAN(arg);
    return true;
}

void Konstanta::Ispis() const {
    cout << _Vrednost;
}

double Konstanta::Izracunaj() const {
    return _Vrednost;
}

Izraz* Konstanta::Izvod(char x) const {
    NEBITAN(x);
    return new Konstanta(0);
}

Izraz* Konstanta::Kopija() const {
    return new Konstanta(_Vrednost);
}

//////////////////////////////////////////////////////////////////////

bool Promenljiva::Provera(const vector<char>& arg) const {
    for(char c : arg)
        if(c == _Naziv)
            return true;
    return false;
}

void Promenljiva::Ispis() const {
    cout << _Naziv;
}

double Promenljiva::Izracunaj() const {
    return promenljive[_Naziv];
}

Izraz* Promenljiva::Izvod(char x) const {
    return _Naziv == x ? new Konstanta(1) : new Konstanta(0);
}

Izraz* Promenljiva::Kopija() const {
    return new Promenljiva(_Naziv);
}

//////////////////////////////////////////////////////////////////////

UnarniIzraz::UnarniIzraz(const UnarniIzraz& i) {
    _Argument = i._Argument->Kopija();
}

bool UnarniIzraz::Provera(const vector<char>& arg) const {
    return _Argument->Provera(arg);
}

UnarniIzraz::~UnarniIzraz() {
    delete _Argument;
}

void Sinus::Ispis() const {
    cout << "sin(";
    _Argument->Ispis();
    cout << ")";
}

double Sinus::Izracunaj() const {
    return sin(_Argument->Izracunaj());
}

Izraz* Sinus::Izvod(char x) const {
    return new Proizvod(
      new Kosinus(_Argument->Kopija()), _Argument->Izvod(x));
}

Izraz* Sinus::Kopija() const {
    return new Sinus(_Argument->Kopija());
}

void Kosinus::Ispis() const {
    cout << "cos(";
    _Argument->Ispis();
    cout << ")";
}

double Kosinus::Izracunaj() const {
    return cos(_Argument->Izracunaj());
}

Izraz* Kosinus::Izvod(char x) const {
    return new Proizvod(
      new Proizvod(new Konstanta(-1), new Sinus(_Argument->Kopija())), _Argument->Izvod(x));
}

Izraz* Kosinus::Kopija() const {
    return new Kosinus(_Argument->Kopija());
}

//////////////////////////////////////////////////////////////////////

BinarniIzraz::BinarniIzraz(const BinarniIzraz& i) {
    _Levi = i._Levi->Kopija();
    _Desni = i._Desni->Kopija();
}

bool BinarniIzraz::Provera(const vector<char>& arg) const {
    return _Levi->Provera(arg) && _Desni->Provera(arg);
}

BinarniIzraz::~BinarniIzraz() {
    delete _Levi;
    delete _Desni;
}

void Zbir::Ispis() const {
    cout << "(";
    _Levi->Ispis();
    cout << ")+(";
    _Desni->Ispis();
    cout << ")";
}

double Zbir::Izracunaj() const {
    return _Levi->Izracunaj() + _Desni->Izracunaj();
}

Izraz* Zbir::Izvod(char x) const {
    return new Zbir(_Levi->Izvod(x), _Desni->Izvod(x));
}

Izraz* Zbir::Kopija() const {
    return new Zbir(_Levi->Kopija(), _Desni->Kopija());
}

void Proizvod::Ispis() const {
    cout << "(";
    _Levi->Ispis();
    cout << ")*(";
    _Desni->Ispis();
    cout << ")";
}

double Proizvod::Izracunaj() const {
    return _Levi->Izracunaj() * _Desni->Izracunaj();
}

Izraz* Proizvod::Izvod(char x) const {
    return new Zbir(
        new Proizvod(_Levi->Izvod(x), _Desni->Kopija()),
        new Proizvod(_Levi->Kopija(), _Desni->Izvod(x)));
}

Izraz* Proizvod::Kopija() const {
    return new Proizvod(_Levi->Kopija(), _Desni->Kopija());
}
