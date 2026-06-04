#include "polinomi.hpp"
#include <cmath>

std::ostream& operator<<(std::ostream& izlaz, const Polinom& p) {
    std::vector<double> koef = p.getKoef();

    bool prvi = true;
    for (size_t i = 0; i < koef.size(); i++) {
        if (koef[i] == 0) {
            continue;
        }

        char znak = (koef[i] < 0) ? '-' : '+';
        if (!prvi) {
            izlaz << " " << znak << " ";
        } else {
            if (znak == '-') {
                izlaz << " " << znak << " ";
            }
            prvi = false;
        }

        double absKoef = fabs(koef[i]); 
        if (absKoef != 1 || i == 0) {
            izlaz << absKoef;
        }

        if (i >= 1) {
            izlaz << "x";
            if (i > 1) {
                izlaz << "^" << i;
            }
        }
    }

    return izlaz;
}

Polinom::Polinom(const std::vector<double>& koef) 
    : koef_(koef) {}

std::vector<double> Polinom::getKoef() const {
    return koef_;
}

Polinom Polinom::operator+(const Polinom& p) const {
    std::vector<double> rezultat(std::max(koef_.size(), p.koef_.size()));

    for (size_t i = 0; i < rezultat.size(); i++) {
        double koef1 = (i < koef_.size()) ? koef_[i] : 0;
        double koef2 = (i < p.koef_.size()) ? p.koef_[i] : 0;
        rezultat[i] = koef1 + koef2;
    }

    return Polinom(rezultat);
}

Polinom Polinom::operator-(const Polinom& p) const {
    std::vector<double> rezultat(std::max(koef_.size(), p.koef_.size()));

    for (size_t i = 0; i < rezultat.size(); i++) {
        double koef1 = (i < koef_.size()) ? koef_[i] : 0;
        double koef2 = (i < p.koef_.size()) ? p.koef_[i] : 0;
        rezultat[i] = koef1 - koef2;
    }

    return Polinom(rezultat);
}

Polinom Polinom::operator*(const Polinom& p) const {
    std::vector<double> rezultat(koef_.size() + p.koef_.size() - 1);

    for (size_t i = 0; i < koef_.size(); i++) {
        for (size_t j = 0; j < p.koef_.size(); j++) {
            rezultat[i + j] += koef_[i] * p.koef_[j];
        }
    }

    return Polinom(rezultat);
}

Polinom Polinom::operator-() const {
    std::vector<double> rezultat(koef_.size());

    for (size_t i = 0; i < koef_.size(); i++) {
        rezultat[i] = - koef_[i];
    }

    return Polinom(rezultat);
}
