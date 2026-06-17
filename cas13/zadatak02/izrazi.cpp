#include "izrazi.hpp"

/////////////////////////////////////////////////

int Konstanta::izracunaj() const {
    return vrednost_;
}

Izraz* Konstanta::klon() const {
    return new Konstanta(vrednost_);
}

/////////////////////////////////////////////////

int Promenljiva::izracunaj() const {
    return promenljive[id_];
}

Izraz* Promenljiva::klon() const {
    return new Promenljiva(id_);
}

/////////////////////////////////////////////////

int Sabiranje::izracunaj() const {
    return levi_->izracunaj() + desni_->izracunaj();
}

Izraz* Sabiranje::klon() const {
    return new Sabiranje(levi_->klon(), desni_->klon());
}

int Mnozenje::izracunaj() const {
    return levi_->izracunaj() * desni_->izracunaj();
}

Izraz* Mnozenje::klon() const {
    return new Mnozenje(levi_->klon(), desni_->klon());
}   

int DeljenjeOstatak::izracunaj() const {
    return levi_->izracunaj() % desni_->izracunaj();
}

Izraz* DeljenjeOstatak::klon() const {
    return new DeljenjeOstatak(levi_->klon(), desni_->klon());
}  

int Manje::izracunaj() const {
    return levi_->izracunaj() < desni_->izracunaj();
}

Izraz* Manje::klon() const {
    return new Manje(levi_->klon(), desni_->klon());
}  

int Vece::izracunaj() const {
    return levi_->izracunaj() > desni_->izracunaj();
}

Izraz* Vece::klon() const {
    return new Vece(levi_->klon(), desni_->klon());
}  