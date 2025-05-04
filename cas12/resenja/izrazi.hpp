#ifndef IZRAZI_HPP
#define IZRAZI_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

#define NEBITAN(x) (void(x))

using namespace std;

class Izraz {
public:
    virtual ~Izraz() {}
    virtual int Izracunaj() const = 0;
    virtual Izraz* Kopija() const = 0;
};

class Konstanta : public Izraz {
public:
    Konstanta(int vrijednost)
        : _Vrednost(vrijednost) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
private:
    int _Vrednost;
};

class Promenljiva : public Izraz {
public:
    Promenljiva(const string& naziv)
        : _Naziv(naziv) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
private:
    string _Naziv;
};

class UnarniIzraz : public Izraz {
public:
    ~UnarniIzraz();
    UnarniIzraz(Izraz* argument)
        : _Argument(argument) {}
protected:
    UnarniIzraz(const UnarniIzraz& i);
    UnarniIzraz& operator =(const UnarniIzraz& i);

    Izraz* _Argument;
};

class BinarniIzraz : public Izraz {
public:
    ~BinarniIzraz();
    BinarniIzraz(Izraz* levi, Izraz* desni)
        : _Levi(levi), _Desni(desni) {}
private:
    BinarniIzraz(const BinarniIzraz&);
    BinarniIzraz& operator =(const UnarniIzraz&);
protected:
    Izraz* _Levi;
    Izraz* _Desni;
};

class Zbir : public BinarniIzraz {
public:
    Zbir(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
};

class Proizvod : public BinarniIzraz {
public:
    Proizvod(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
};

class Mod : public BinarniIzraz {
public:
    Mod(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
};

class Vece : public BinarniIzraz {
public:
    Vece(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
};

class Manje : public BinarniIzraz {
public:
    Manje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
};

class Sinus : public UnarniIzraz {
public:
    Sinus(Izraz* argument)
        : UnarniIzraz(argument) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
};

class Kosinus : public UnarniIzraz {
public:
    Kosinus(Izraz* argument)
        : UnarniIzraz(argument) {}
    int Izracunaj() const;
    Izraz* Kopija() const;
};


#endif
