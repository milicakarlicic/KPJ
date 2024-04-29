#include <iostream>
#include <string>

using namespace std;

class Student {
public:
    Student(string alas, double prosek, Student *bff = nullptr)
        : _Alas(alas), _Prosek(prosek), _BFF(bff) {}

    virtual ~Student() {
        // kada podrazumijevani destruktor nije dovoljan?
        cout << "destruktor s" << endl;
        if (_BFF != nullptr) {
            delete _BFF;
        }
    }

    virtual void Ispis() const {
        cout << _Alas << ": " << _Prosek;
        if (_BFF != nullptr) {
            cout << ", bff: " << _BFF->_Alas;
        } else {
            cout << ", bff: nemam ga :(";
        }
    }
protected:
    string _Alas;
    double _Prosek;
    Student *_BFF;
};

class StudentSaR : public Student {
public:
    StudentSaR(string alas, double prosek, int ocenaKPJ, Student *bff = nullptr)
        : Student(alas, prosek, bff), _OcenaKPJ(ocenaKPJ) {}

    ~StudentSaR() {
        cout << "destruktor s sa R" << endl;
    }

    void Ispis() const {
        Student::Ispis();
        cout << ", ocena iz KPJ: " << _OcenaKPJ;
    }
private:
    int _OcenaKPJ;
};

class StudentSaM : public Student {
public:
    StudentSaM(string alas, double prosek, int ocenaTPG, Student *bff = nullptr)
        : Student(alas, prosek, bff), _OcenaTPG(ocenaTPG) {}

    ~StudentSaM() {
        cout << "destruktor s sa M" << endl;
    }

    void Ispis() const {
        Student::Ispis();
        cout << ", ocena iz TPG: " << _OcenaTPG;
    }
private:
    int _OcenaTPG;
};

int main() {
    Student* niz[] = {new StudentSaM("mm21002", 6.5, 6),
                      new StudentSaR("mr21118", 10, 10, new StudentSaR("mr21049", 10, 10)),
                      new Student("mv21003", 8.5, new StudentSaM("mm22019", 10, 10))};

    for (auto element : niz) {
        element->Ispis();
        cout << endl;
    }

    for (auto element : niz) {
        delete element;
    }
}
