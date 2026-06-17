#include <iostream>
#include <vector>
#include <map>

//////////////////////////////////////////////////////////////////

class Izraz {
public:
    virtual ~Izraz() {}

    virtual bool provera(const std::vector<char>& arg) const = 0;
    virtual void ispisi() const = 0;
    virtual double izracunaj(const std::map<char, double>& promenljive) const = 0;
    virtual Izraz* izvod(char prom) const = 0;
    virtual Izraz* klon() const = 0;
};

//////////////////////////////////////////////////////////////////

class Konstanta : public Izraz {
public:
    Konstanta(double vrednost)
        : vrednost_(vrednost) {}

    bool provera(const std::vector<char>& arg) const override;
    void ispisi() const override;
    double izracunaj(const std::map<char, double>& promenljive) const override;
    Izraz* izvod(char prom) const override;
    Izraz* klon() const override;
private:
    double vrednost_;
};

//////////////////////////////////////////////////////////////////

class Promenljiva : public Izraz {
public:
    Promenljiva(char id) 
        : id_(id) {}

    bool provera(const std::vector<char>& arg) const override;
    void ispisi() const override;
    double izracunaj(const std::map<char, double>& promenljive) const override;
    Izraz* izvod(char prom) const override;
    Izraz* klon() const override;
private:
    char id_;
};

//////////////////////////////////////////////////////////////////

class UnarniIzraz : public Izraz {
public:
    UnarniIzraz(Izraz* operand)
        : operand_(operand) {}

    ~UnarniIzraz() override {
        delete operand_;
    }

    UnarniIzraz(const UnarniIzraz&) = delete;
    UnarniIzraz& operator=(const UnarniIzraz&) = delete;

    bool provera(const std::vector<char>& arg) const override;
protected:
    Izraz* operand_;
};

class Sinus : public UnarniIzraz {
public:
    Sinus(Izraz* operand) 
        : UnarniIzraz(operand) {}

    void ispisi() const override;
    double izracunaj(const std::map<char, double>& promenljive) const override;
    Izraz* izvod(char prom) const override;
    Izraz* klon() const override;
};

class Kosinus : public UnarniIzraz {
public:
    Kosinus(Izraz* operand) 
        : UnarniIzraz(operand) {}

    void ispisi() const override;
    double izracunaj(const std::map<char, double>& promenljive) const override;
    Izraz* izvod(char prom) const override;
    Izraz* klon() const override;
};

//////////////////////////////////////////////////////////////////

class BinarniIzraz : public Izraz {
public:
    BinarniIzraz(Izraz* levi, Izraz* desni)
        : levi_(levi), desni_(desni) {}

    ~BinarniIzraz() override {
        delete levi_;
        delete desni_;
    }

    BinarniIzraz(const BinarniIzraz&) = delete;
    BinarniIzraz& operator=(const BinarniIzraz&) = delete;

    bool provera(const std::vector<char>& arg) const override;
protected:    
    Izraz* levi_;
    Izraz* desni_;
};

class Sabiranje : public BinarniIzraz {
public:
    Sabiranje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}

    void ispisi() const override;
    double izracunaj(const std::map<char, double>& promenljive) const override;
    Izraz* izvod(char prom) const override;
    Izraz* klon() const override;
};  

class Mnozenje : public BinarniIzraz {
public:
    Mnozenje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}

    void ispisi() const override;
    double izracunaj(const std::map<char, double>& promenljive) const override;
    Izraz* izvod(char prom) const override;
    Izraz* klon() const override;
}; 

//////////////////////////////////////////////////////////////////

class Funkcija {
public:
    Funkcija(const std::vector<char>& arg,
         Izraz* izraz)
        : arg_(arg), izraz_(izraz) {}

    ~Funkcija() {
        delete izraz_;
    }

    Funkcija(const Funkcija&) = delete;
    Funkcija& operator=(const Funkcija&) = delete;

    bool provera(const std::vector<char>& arg) const;
    // za domaci: implementirati operator<< za ispis funkcije
    void ispisi() const;
    double operator[](const std::vector<double>& vrednostiArg) const;
    Funkcija* izvod(char prom) const;
private:
    std::vector<char> arg_;
    Izraz* izraz_;
};