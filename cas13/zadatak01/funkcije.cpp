#include "funkcije.hpp"
#include <cmath>

extern void yyerror(const std::string& poruka);

//////////////////////////////////////////////////////////////////

bool Konstanta::provera(const std::vector<char>& arg) const {
    return true;
}

void Konstanta::ispisi() const {
    std::cout << vrednost_;
}

double Konstanta::izracunaj(const std::map<char, double>& promenljive) const {
    return vrednost_;
}

Izraz* Konstanta::izvod(char prom) const {
    return new Konstanta(0);
}

Izraz* Konstanta::klon() const {
    return new Konstanta(vrednost_);
}

//////////////////////////////////////////////////////////////////

bool Promenljiva::provera(const std::vector<char>& arg) const {
    for (char c : arg) {
        if (c == id_) {
            return true;
        }
    }
    
    return false;
}

void Promenljiva::ispisi() const {
    std::cout << id_;
}

double Promenljiva::izracunaj(const std::map<char, double>& promenljive) const {
    // metoda at umesto [] jer je const za objekat nad kojim se poziva
    return promenljive.at(id_);
}

Izraz* Promenljiva::izvod(char prom) const {
    return prom == id_ ? new Konstanta(1) : new Konstanta(0);
}

Izraz* Promenljiva::klon() const {
    return new Promenljiva(id_);
}

//////////////////////////////////////////////////////////////////

bool UnarniIzraz::provera(const std::vector<char>& arg) const {
    return operand_->provera(arg);
}

void Sinus::ispisi() const {
    std::cout << "sin(";
    operand_->ispisi();
    std::cout << ")";
}

double Sinus::izracunaj(const std::map<char, double>& promenljive) const {
    return sin(operand_->izracunaj(promenljive));
}

Izraz* Sinus::izvod(char prom) const {
    return new Mnozenje(
        new Kosinus(operand_->klon()),
        operand_->izvod(prom)
    );
}

Izraz* Sinus::klon() const {
    return new Sinus(operand_->klon());
}

void Kosinus::ispisi() const {
    std::cout << "cos(";
    operand_->ispisi();
    std::cout << ")";
}

double Kosinus::izracunaj(const std::map<char, double>& promenljive) const {
    return cos(operand_->izracunaj(promenljive));
}

Izraz* Kosinus::izvod(char prom) const {
    return new Mnozenje(
        new Mnozenje(
            new Konstanta(-1),
            new Sinus(operand_->klon())
        ),
        operand_->izvod(prom)
    );
}

Izraz* Kosinus::klon() const {
    return new Kosinus(operand_->klon());
}

//////////////////////////////////////////////////////////////////

bool BinarniIzraz::provera(const std::vector<char>& arg) const {
    return levi_->provera(arg) && desni_->provera(arg);
}

void Sabiranje::ispisi() const {
    std::cout << "(";
    levi_->ispisi();
    std::cout << ") + (";
    desni_->ispisi();
    std::cout << ")";
}

double Sabiranje::izracunaj(const std::map<char, double>& promenljive) const {
    return levi_->izracunaj(promenljive) +
        desni_->izracunaj(promenljive); 
}

Izraz* Sabiranje::izvod(char prom) const {
    return new Sabiranje(
        levi_->izvod(prom),
        desni_->izvod(prom)
    );
}

Izraz* Sabiranje::klon() const {
    return new Sabiranje(levi_->klon(), desni_->klon());
}

void Mnozenje::ispisi() const {
    std::cout << "(";
    levi_->ispisi();
    std::cout << ") * (";
    desni_->ispisi();
    std::cout << ")";
}

double Mnozenje::izracunaj(const std::map<char, double>& promenljive) const {
    return levi_->izracunaj(promenljive) *
        desni_->izracunaj(promenljive); 
}

Izraz* Mnozenje::izvod(char prom) const {
    return new Sabiranje(
        new Mnozenje(
            levi_->izvod(prom), 
            desni_->klon()
        ),
        new Mnozenje(
            levi_->klon(),
            desni_->izvod(prom)
        )
    );
}

Izraz* Mnozenje::klon() const {
    return new Mnozenje(levi_->klon(), desni_->klon());
}

//////////////////////////////////////////////////////////////////

bool Funkcija::provera(const std::vector<char>& arg) const {
    return izraz_->provera(arg);
}

void Funkcija::ispisi() const {
    izraz_->ispisi();
    std::cout << std::endl;
}

double Funkcija::operator[](const std::vector<double>& vrednostiArg) const {
    if (arg_.size() != vrednostiArg.size()) {
        yyerror("Neodgovarajuci broj argumenata funkcije!");
    }

    std::map<char, double> promenljive;

    for (size_t i = 0; i < arg_.size(); i++) {
        promenljive[arg_[i]] = vrednostiArg[i];
    }

    return izraz_->izracunaj(promenljive);
}

Funkcija* Funkcija::izvod(char prom) const {
    bool postojiProm = false;
    for (char c : arg_) {
        if (c == prom) {
            postojiProm = true;
            break;
        }
    }
    if (!postojiProm) {
        yyerror("Promenljiva po kojoj trazis izvod nije definisana!");
    }

    return new Funkcija(arg_, izraz_->izvod(prom));
}