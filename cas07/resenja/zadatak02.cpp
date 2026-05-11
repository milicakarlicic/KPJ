#include <iostream>

class Razlomak {
public:
    explicit Razlomak(int brojilac = 0, int imenilac = 1)
        : brojilac_(brojilac), imenilac_(imenilac) {}

    int getBrojilac() const {
        return brojilac_;
    }

    int getImenilac() const {
        return imenilac_;
    }

    void setBrojilac(int brojilac) {
        brojilac_ = brojilac;
    }

    void setImenilac(int imenilac) {
        if (imenilac != 0) {
            imenilac_ = imenilac;
        }
    }

    Razlomak operator+(const Razlomak& r) const {
        return Razlomak(
            brojilac_ * r.imenilac_ + r.brojilac_ * imenilac_,
            imenilac_ * r.imenilac_
        );
    }

    Razlomak operator-(const Razlomak& r) const {
        return Razlomak(
            brojilac_ * r.imenilac_ - r.brojilac_ * imenilac_,
            imenilac_ * r.imenilac_
        );
    }

    Razlomak operator*(const Razlomak& r) const {
        return Razlomak(
            brojilac_ * r.brojilac_,
            imenilac_ * r.imenilac_
        );
    }

    Razlomak operator/(const Razlomak& r) const {
        return Razlomak(
            brojilac_ * r.imenilac_,
            imenilac_ * r.brojilac_
        );
    }

    Razlomak operator++(int) {
        Razlomak r(*this);
        brojilac_ += imenilac_;
        return r;
    }

    Razlomak& operator++() {
        brojilac_ += imenilac_;
        return *this;
    }

    operator double() const {
        return 1.0 * brojilac_ / imenilac_;
    }

private:
    int brojilac_;
    int imenilac_;
};

std::ostream& operator<<(std::ostream& izlaz, const Razlomak& r) {
    izlaz << r.getBrojilac() << "/" << r.getImenilac();
    return izlaz;
}

std::istream& operator>>(std::istream& ulaz, Razlomak& r) {
    int brojilac, imenilac;
    char znak;

    ulaz >> brojilac >> znak >> imenilac;

    if (znak != '/' || imenilac == 0) {
        std::cerr << "Neispravan unos razlomka!" << std::endl;
        exit(EXIT_FAILURE);
    }

    r.setBrojilac(brojilac);
    r.setImenilac(imenilac);

    return ulaz;
}

int main() {
    Razlomak r1, r2;

    std::cout << "Unesite prvi razlomak: ";
    std::cin >> r1;

    std::cout << "Unesite drugi razlomak: ";
    std::cin >> r2;

    std::cout << "\nr1 = " << r1 << std::endl;
    std::cout << "r2 = " << r2 << std::endl;

    std::cout << "\nr1 + r2 = " << r1 + r2 << std::endl;

    std::cout << "\nPostfiksno inkrementiranje r1++: " << r1++ << std::endl;
    std::cout << "Nakon inkrementiranja: " << r1 << std::endl;

    std::cout << "\nPrefiksno inkrementiranje ++r2: " << ++r2 << std::endl;

    // Implicitna konverzija razlomka u double
    std::cout << r1 + 2 << std::endl;

    return 0;
}