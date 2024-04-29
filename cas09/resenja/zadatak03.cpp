#include <iostream>
#include <string>

using namespace std;

class Student {
  public:
    Student() {}

    Student(const string& alas)
      : _Alas(alas) {}

    virtual ~Student() {
      cout << "~Student" << endl;
    }

    // apstraktni (cisto virtualni) metod: virtual void Ispis() const = 0
    virtual void Ispis() const {
      cout << "Ja sam student " + _Alas << endl;
    }

    string VratiAlas() const {
      return _Alas;
    }

  private:
    string _Alas;
};

class StudentSaR : public Student {
  public:
    StudentSaR(const string& alas, int ocena = 5)
      : Student(alas), _OcenaKPJ(ocena) {}

    ~StudentSaR() {
      cout << "~StudentSaR" << endl;
    }

    void Ispis() const {
      cout << "Ja sam student " + this->VratiAlas() << " sa ocenom " << _OcenaKPJ << " iz KPJ" << endl;
    }
  private:
    int _OcenaKPJ;
};

class StudentSaM : public Student {
  public:
    StudentSaM(const string& alas, int ocena = 5)
      : Student(alas), _OcenaTPG(ocena) {}

    ~StudentSaM() {
      cout << "~StudentSaM" << endl;
    }

    void Ispis() const {
      cout << "Ja sam student " + this->VratiAlas() << " sa ocenom " << _OcenaTPG << " iz TPG" << endl;
    }
  private:
    int _OcenaTPG;
};

// poziv Valgrind-a: valgrind ./a.out
// dobro bi bilo prevodjenje izvrsiti sa opcijom -g kako bi se generisali debug simboli i
// kako bismo imali informaciju u kojoj liniji se desilo curenje memorije

int main() {
    Student* niz[3];

    niz[0] = new Student("mr22022");
    niz[1] = new StudentSaR("mi22100", 10);
    niz[2] = new StudentSaM("mm21001", 9);

    for (Student *s : niz) {
        s->Ispis();
    }

    for (Student *s : niz) {
        delete s;
    }

    return 0;
}
