#ifndef IZRAZI_HPP
#define IZRAZI_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

extern std::map<std::string, int> promenljive;

////////////////////////////////////////////////////////////

class Izraz {
public:
    virtual ~Izraz() {}

    virtual int izracunaj() const = 0;
    virtual Izraz* klon() const = 0;
};

////////////////////////////////////////////////////////////

class Konstanta : public Izraz {
public:
    Konstanta(int vrednost)
        : vrednost_(vrednost) {}

    int izracunaj() const override;
    Izraz* klon() const override;
private:
    int vrednost_;
};

////////////////////////////////////////////////////////////

class Promenljiva : public Izraz {
public:
    Promenljiva(const std::string& id)
        : id_(id) {}

    int izracunaj() const override;
    Izraz* klon() const override;
private:
    std::string id_;
};

////////////////////////////////////////////////////////////

class BinarniIzraz : public Izraz {
public:
    ~BinarniIzraz() override {
        delete levi_;
        delete desni_;
    }

    BinarniIzraz(Izraz* levi, Izraz* desni)
        : levi_(levi), desni_(desni) {}

    BinarniIzraz(const BinarniIzraz& i) = delete;
    BinarniIzraz& operator=(const BinarniIzraz& i) = delete;
protected:
    Izraz* levi_;
    Izraz* desni_;
};

class Sabiranje : public BinarniIzraz {
public:
    Sabiranje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}

    int izracunaj() const override;
    Izraz* klon() const override;
};

class Mnozenje : public BinarniIzraz {
public:
    Mnozenje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}

    int izracunaj() const override;
    Izraz* klon() const override;
};

class DeljenjeOstatak : public BinarniIzraz {
public:
    DeljenjeOstatak(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}

    int izracunaj() const override;
    Izraz* klon() const override;
};

class Vece : public BinarniIzraz {
public:
    Vece(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}

    int izracunaj() const override;
    Izraz* klon() const override;
};

class Manje : public BinarniIzraz {
public:
    Manje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}

    int izracunaj() const override;
    Izraz* klon() const override;
};

#endif