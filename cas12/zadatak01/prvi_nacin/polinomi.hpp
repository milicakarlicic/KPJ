#ifndef POLINOMI_HPP
#define POLINOMI_HPP

#include <iostream>
#include <vector>

class Polinom {
public:
    Polinom(const std::vector<double>& koef);

    std::vector<double> getKoef() const;
    Polinom operator+(const Polinom& p) const;
    Polinom operator-(const Polinom& p) const;
    Polinom operator*(const Polinom& p) const;
    Polinom operator-() const;
    bool operator==(const Polinom& p) const;
    bool operator!=(const Polinom& p) const;
    double operator[](double x) const;
    Polinom izvod() const;
    Polinom integral(double c) const;
private:
    std::vector<double> koef_;
};

std::ostream& operator<<(std::ostream& izlaz, const Polinom& p);

#endif