#ifndef FUNKCIJE_HPP
#define FUNKCIJE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#define NEBITAN(x) (void(x))

using namespace std;

class Izraz {
public:
	// BITNO DA DESTRUKTOR BUDE VIRTUAL!!!
    virtual ~Izraz() {}
    virtual bool Provera(const vector<char>& arg) const = 0;
    virtual void Ispis() const = 0;
    virtual double Izracunaj() const = 0;
    virtual Izraz* Izvod(char x) const = 0;
    virtual Izraz* Kopija() const = 0;
};

class Konstanta : public Izraz {
public:
    Konstanta(double vrednost)
        : _Vrednost(vrednost) {}
    bool Provera(const vector<char>& arg) const;
    void Ispis() const;
    double Izracunaj() const;
    Izraz* Izvod(char x) const;
    Izraz* Kopija() const;
private:
    double _Vrednost;
};

class Promenljiva : public Izraz {
public:
    Promenljiva(char naziv)
        : _Naziv(naziv) {}
    bool Provera(const vector<char>& arg) const;
    void Ispis() const;
    double Izracunaj() const;
    Izraz* Izvod(char x) const;
    Izraz* Kopija() const;
private:
    char _Naziv;
};

class UnarniIzraz : public Izraz {
public:
    ~UnarniIzraz();
    UnarniIzraz(Izraz* argument)
        : _Argument(argument) {}
    bool Provera(const vector<char>& arg) const;
private:
    UnarniIzraz(const UnarniIzraz&);
    UnarniIzraz& operator =(const UnarniIzraz&);
protected:
    Izraz* _Argument;
};

class Sinus : public UnarniIzraz {
public:
    Sinus(Izraz* argument)
        : UnarniIzraz(argument) {}
    void Ispis() const;
    double Izracunaj() const;
    Izraz* Izvod(char x) const;
    Izraz* Kopija() const;
};

class Kosinus : public UnarniIzraz {
public:
    Kosinus(Izraz* argument)
        : UnarniIzraz(argument) {}
    void Ispis() const;
    double Izracunaj() const;
    Izraz* Izvod(char x) const;
    Izraz* Kopija() const;
};

class BinarniIzraz : public Izraz {
public:
    ~BinarniIzraz();
    BinarniIzraz(Izraz* levi, Izraz* desni)
        : _Levi(levi), _Desni(desni) {}
    bool Provera(const vector<char>& arg) const;
private:
    BinarniIzraz(const BinarniIzraz&);
    BinarniIzraz& operator =(const BinarniIzraz&);
protected:
    Izraz* _Levi;
    Izraz* _Desni;
};

class Zbir : public BinarniIzraz {
public:
    Zbir(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
    void Ispis() const;
    double Izracunaj() const;
    Izraz* Izvod(char x) const;
    Izraz* Kopija() const;
};

class Proizvod : public BinarniIzraz {
public:
    Proizvod(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
    void Ispis() const;
    double Izracunaj() const;
    Izraz* Izvod(char x) const;
    Izraz* Kopija() const;
};

class Funkcija {
public:
    Funkcija(const vector<char>& arg, Izraz* izraz)
        : _Arg(arg), _Izraz(izraz) {}
    ~Funkcija();
    bool Provera() const;
    void Ispis() const;
    double operator [](const vector<double>& arg) const;
    Funkcija* Izvod(char x) const;
private:
	// Kako nam nije dovoljan podrazumijevani destruktor, to nam nisu dovoljni ni 
	// podrazumijevani konstruktor kopije ni operator dodjele.
	// Na ovaj nacin sprecavamo korisnika da ih koristi jer ih nismo predefinisali
	// kako treba...
    Funkcija(const Funkcija&);
    Funkcija& operator =(const Funkcija&);
private:
    vector<char> _Arg;
    Izraz* _Izraz;
};


#endif
