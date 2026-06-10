#include <iostream>
#include <vector>

class Izraz {

};

class Konstanta : public Izraz {
    Konstanta(double vrednost)
        : vrednost_(vrednost) {}
private:
    double vrednost_;
};

class Promenljiva : public Izraz {
    Promenljiva(char id) 
        : id_(id) {}
private:
    char id_;
};

class UnarniIzraz : public Izraz {
public:
    UnarniIzraz(Izraz* operand)
        : operand_(operand) {}
private:
    Izraz* operand_;
};

class Sinus : public UnarniIzraz {
public:
    Sinus(Izraz* operand) 
        : UnarniIzraz(operand) {}
};

class Kosinus : public UnarniIzraz {
public:
    Kosinus(Izraz* operand) 
        : UnarniIzraz(operand) {}
};

class BinarniIzraz : public Izraz {
public:
    BinarniIzraz(Izraz* levi, Izraz* desni)
        : levi_(levi), desni_(desni) {}
private:    
    Izraz* levi_;
    Izraz* desni_;
};

class Sabiranje : public BinarniIzraz {
public:
    Sabiranje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
};  

class Mnozenje : public BinarniIzraz {
public:
    Mnozenje(Izraz* levi, Izraz* desni)
        : BinarniIzraz(levi, desni) {}
}; 

class Funkcija {
public:
    Funkcija(const std::vector<char>& arg, Izraz* izraz)
        : arg_(arg), izraz_(izraz) {}

    ~Funkcija() {
        delete izraz_;
    }

    Funkcija(const Funkcija& f) = delete;
    Funkcija& operator=(const Funkcija& f) = delete;
private:
    std::vector<char> arg_;
    Izraz* izraz_;
};