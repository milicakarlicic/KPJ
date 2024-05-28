#ifndef FUNKCIJE_HPP
#define FUNKCIJE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <set>

#define NEBITAN(x) (void(x))

using namespace std;

class Izraz {
public:
    virtual ~Izraz() {}
    virtual void Ispis() const = 0;
    virtual double Izracunaj() const = 0;
    virtual Izraz* Izvod(char x) const = 0;
    virtual Izraz* Kopija() const = 0;
    set<char>& getPromenljive() {
        return _Promenljive;
    }
protected:
    // Skup promenljivih izraza
    set<char> _Promenljive;
};

class Konstanta : public Izraz {
public:
    Konstanta(double vrednost)
        : _Vrednost(vrednost) {}
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
        : _Naziv(naziv) {
            _Promenljive.insert(_Naziv);
        }
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
        : _Argument(argument) {
            // Promenljive unarnog izraza su promenljive njegovog operanda
            _Promenljive = argument->getPromenljive();
        }
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
        : _Levi(levi), _Desni(desni) {
            // Promenljive binarnog izraza su promenljive njegovog lijevog izraza na koje su dodate i promenljive desnog izraza
            _Promenljive = _Levi->getPromenljive();
            _Promenljive.insert(_Desni->getPromenljive().begin(), _Desni->getPromenljive().end());
        }
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
    Funkcija(const Funkcija&);
    Funkcija& operator =(const Funkcija&);
private:
    vector<char> _Arg;
    Izraz* _Izraz;
};


#endif
