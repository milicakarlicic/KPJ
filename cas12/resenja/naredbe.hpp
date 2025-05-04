#ifndef NAREDBE_HPP
#define NAREDBE_HPP

#include <string>
#include <map>
#include "izrazi.hpp"

using namespace std;

class Naredba {
public:
    virtual ~Naredba() {}
    virtual void Izvrsi() const = 0;
};

class Blok : public Naredba {
public:
    Blok(const vector<Naredba*>& n)
        : _Naredbe(n) {}
    ~Blok();
    void Izvrsi() const;
private:
    Blok(const Blok&);
    Blok& operator =(const Blok&);

    vector<Naredba*> _Naredbe;
};

class IspisS : public Naredba {
public:
    IspisS(const string& s)
        : _String(s) {}
    void Izvrsi() const;
private:
    string _String;
};

class IspisE : public Naredba {
public:
    IspisE(Izraz* i)
        :  _Izraz(i) {}
    ~IspisE();
    void Izvrsi() const;
private:
    IspisE(const IspisE&);
    IspisE& operator =(const IspisE&);

    Izraz* _Izraz;
};

class Dodjela : public Naredba {
public:
    Dodjela(const string& id, Izraz* i)
        : _Id(id), _Izraz(i) {}
    ~Dodjela();
    void Izvrsi() const;
private:
    Dodjela(const Dodjela&);
    Dodjela& operator =(const Dodjela&);

    string _Id;
    Izraz* _Izraz;
};

class Unesi : public Naredba {
public:
    Unesi(const string& id)
        : _Id(id) {}
    void Izvrsi() const;
private:
    string _Id;
};

class UslovSaInace : public Naredba {
public:
    UslovSaInace(Izraz* i, Naredba* n1, Naredba* n2)
        : _Izraz(i), _N1(n1), _N2(n2) {}
    ~UslovSaInace();
    void Izvrsi() const;
private:
    UslovSaInace(const UslovSaInace&);
    UslovSaInace& operator =(const UslovSaInace&);

    Izraz* _Izraz;
    Naredba* _N1;
    Naredba* _N2;
};

class UslovBezInace : public Naredba {
public:
    UslovBezInace(Izraz* i, Naredba* n)
        : _Izraz(i), _N(n) {}
    ~UslovBezInace();
    void Izvrsi() const;
private:
    UslovBezInace(const UslovBezInace&);
    UslovBezInace& operator =(const UslovBezInace&);

    Izraz* _Izraz;
    Naredba* _N;
};

class Petlja : public Naredba {
public:
    Petlja(Izraz* i, Naredba* n)
        : _Izraz(i), _Naredba(n) {}
    ~Petlja();
    void Izvrsi() const;
private:
    Petlja(const Petlja&);
    Petlja& operator =(const Petlja&);

    Izraz* _Izraz;
    Naredba* _Naredba;
};

#endif
