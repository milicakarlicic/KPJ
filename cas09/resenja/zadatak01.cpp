#include <iostream>
#include <map>
#include <vector>

class Student {
public:
    Student() {}

    Student(const std::string& alas, double prosek, Student* bff = nullptr)
        : alas_(alas), prosek_(prosek), bff_(bff) {} // domaci: duboko kopirati bff objekat (metoda kloniranja)

    virtual ~Student() {
        std::cout << "~Student\n";
        if (bff_ != nullptr) {
            delete bff_;
        }
    }

    // brisemo copy konstruktor i operator dodele da bismo izbegli probleme sa dubokim kopiranjem
    Student(const Student& s) = delete;

    Student& operator=(const Student& s) = delete;

    virtual void ispisi(std::ostream& izlaz) const {
        izlaz << alas_ << " " << prosek_;
        if (bff_ != nullptr) {
            izlaz << ", bff: " << bff_->alas_;
        }
    }

protected:
    std::string alas_;
    double prosek_;
    Student* bff_;
};

class StudentSaR : public Student {
public:
    StudentSaR(const std::string& alas, double prosek, 
        int ocenaKPJ, Student* bff = nullptr)
        : Student(alas, prosek, bff), ocenaKPJ_(ocenaKPJ) {}

    ~StudentSaR() override {
        std::cout << "~StudentSaR\n";
    }

    void ispisi(std::ostream& izlaz) const override {
        Student::ispisi(izlaz);
        izlaz << ", ocena iz KPJ: "
              << ocenaKPJ_;
    }

private:
    int ocenaKPJ_;
};

class StudentSaM : public Student {
public:
    StudentSaM(const std::string& alas, double prosek, 
        int ocenaTPG, Student* bff = nullptr)
        : Student(alas, prosek, bff), ocenaTPG_(ocenaTPG) {}

    ~StudentSaM() override {
        std::cout << "~StudentSaM\n";
    }

    void ispisi(std::ostream& izlaz) const override {
        Student::ispisi(izlaz);
        izlaz << ", ocena iz TPG: "
              << ocenaTPG_;
    }

private:
    int ocenaTPG_;
};

std::ostream& operator<<(std::ostream& izlaz, const Student& s) {
    s.ispisi(izlaz);
    return izlaz;
}

int main() {
    Student* s1 = new Student("mm24001", 9.5);
    Student* s2 = new StudentSaR("mm24002", 9.0, 10, new Student("mm24003", 7.5));
    Student* s3 = new StudentSaM("mm24004", 8.5, 9, new Student("mm24005", 8.7));

    std::vector<Student*> studenti = {s1, s2, s3};

    for (const auto& student : studenti) {
        std::cout << *student << std::endl;
    }

    for (auto& student : studenti) {
        delete student;
    }

    return 0;
}