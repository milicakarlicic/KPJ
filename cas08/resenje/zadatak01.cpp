#include <iostream>
#include <string>

class Student {
public:
    Student() {}

    Student(const std::string& alas, double prosek)
        : alas_(alas), prosek_(prosek) {}

    // Dovoljan podrazumevani destruktor ali ga definisemo zbog ispisa
    virtual ~Student() {
        std::cout << "~Student\n";
    }

    // Dovoljan podrazumevani konstruktor kopije ali ga definisemo zbog ispisa
    Student(const Student& s)
        : alas_(s.alas_), prosek_(s.prosek_) {
        std::cout << "konstruktor kopije\n";
    }

    // Dovoljan podrazumevani operator dodele ali ga definisemo zbog ispisa
    Student& operator=(const Student& s) {
        std::cout << "operator=\n";

        if (this != &s) {
            alas_ = s.alas_;
            prosek_ = s.prosek_;
        }

        return *this;
    }

    virtual void ispisi(std::ostream& izlaz) const = 0;

protected:
    std::string alas_;
    double prosek_;

    // friend std::ostream& operator<<(std::ostream& izlaz, const Student& s);
};

class StudentSaR : public Student {
public:
    StudentSaR(const std::string& alas, double prosek, int ocenaKPJ)
        : Student(alas, prosek), ocenaKPJ_(ocenaKPJ) {}

    ~StudentSaR() override {
        std::cout << "~StudentSaR\n";
    }

    void ispisi(std::ostream& izlaz) const override {
        izlaz << alas_ << " "
              << prosek_
              << ", ocena iz KPJ: "
              << ocenaKPJ_;
    }

private:
    int ocenaKPJ_;
};

class StudentSaM : public Student {
public:
    StudentSaM(const std::string& alas, double prosek, int ocenaTPG)
        : Student(alas, prosek), ocenaTPG_(ocenaTPG) {}

    ~StudentSaM() override {
        std::cout << "~StudentSaM\n";
    }

    void ispisi(std::ostream& izlaz) const override {
        izlaz << alas_ << " "
              << prosek_
              << ", ocena iz TPG: "
              << ocenaTPG_;
    }

private:
    int ocenaTPG_;
};

std::ostream& operator<<(std::ostream& izlaz, const Student& s) {
    // ukoliko koristimo kao friend funkciju:
    // izlaz << s.alas_ << " " << s.prosek_;

    s.ispisi(izlaz);
    return izlaz;
}

// za proveru curenja memorije: valgrind ./a.out
// ukljuciti opciju -g prilikom kompilacije da bi se dobile linije koda u izvestaju valgrinda

int main() {
    // memoriju alociramo dinamicki da bismo mogli da koristimo polimorfizam,
    // tj. da niz pokazivaca na baznu klasu moze da sadrzi objekte izvedenih klasa
    Student* niz[3];

    niz[0] = new StudentSaR("mr23201", 9.5, 10);
    niz[1] = new StudentSaM("mm23105", 8.0, 9);
    niz[2] = new StudentSaR("mr24002", 7.5, 8);

    for (Student* s : niz) {
        std::cout << *s << std::endl;
    }

    for (Student* s : niz) {
        delete s;
    }

    return 0;
}