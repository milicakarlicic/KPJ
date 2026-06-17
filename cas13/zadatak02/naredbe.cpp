#include "naredbe.hpp"

void Blok::izvrsi() const {
    for (const Naredba* n : naredbe_) {
        n->izvrsi();
    }
}

void IspisNiske::izvrsi() const {
    std::cout << niska_ << std::endl;
}

void IspisIzraza::izvrsi() const {
    std::cout << izraz_->izracunaj() << std::endl;
}

void Dodela::izvrsi() const {
    promenljive[id_] = izraz_->izracunaj();
}

void Unesi::izvrsi() const {
    int vrednost;
    std::cin >> vrednost;
    promenljive[id_] = vrednost;
}

void UslovSaInace::izvrsi() const {
    if (izraz_->izracunaj()) {
        n1_->izvrsi();
    } else {
        n2_->izvrsi();
    }
}

void UslovBezInace::izvrsi() const {
    if (izraz_->izracunaj()) {
        n_->izvrsi();
    }
}

void Petlja::izvrsi() const {
    while (izraz_->izracunaj()) {
        naredba_->izvrsi();
    }
}