#include <string>
#include <map>
#include "izrazi.hpp"

////////////////////////////////////////////////////////////

class Naredba {
public:
    virtual ~Naredba() {}

    virtual void izvrsi() const = 0;
};

////////////////////////////////////////////////////////////

class Blok : public Naredba {
public:
    Blok(const std::vector<Naredba*>& naredbe)
        : naredbe_(naredbe) {}

    Blok(Naredba* n) {
        naredbe_.push_back(n);
    }

    ~Blok() override {
        for (Naredba* n : naredbe_) {
            delete n;
        }
    }

    Blok(const Blok&) = delete;
    Blok& operator=(const Blok&) = delete;

    void izvrsi() const override;
private:
    std::vector<Naredba*> naredbe_;
};

////////////////////////////////////////////////////////////

class IspisNiske : public Naredba {
public:
    IspisNiske(const std::string& niska)
        : niska_(niska) {}

    void izvrsi() const override;
private:
    std::string niska_;
};

////////////////////////////////////////////////////////////

class IspisIzraza : public Naredba {
public:
    IspisIzraza(Izraz* izraz)
        : izraz_(izraz) {}

    ~IspisIzraza() override {
        delete izraz_;
    }

    IspisIzraza(const IspisIzraza&) = delete;
    IspisIzraza& operator=(const IspisIzraza&) = delete;

    void izvrsi() const override;
private:
    Izraz* izraz_;
};

////////////////////////////////////////////////////////////

class Dodela : public Naredba {
public:
    Dodela(const std::string& id, Izraz* izraz)
        : id_(id), izraz_(izraz) {}

    ~Dodela() override {
        delete izraz_;
    }

    Dodela(const Dodela&) = delete;
    Dodela& operator=(const Dodela&) = delete;

    void izvrsi() const override;
private:
    std::string id_;
    Izraz* izraz_;
};

////////////////////////////////////////////////////////////

class Unesi : public Naredba {
public:
    Unesi(const std::string& id)
        : id_(id) {}

    void izvrsi() const override;
private:
    std::string id_;
};

////////////////////////////////////////////////////////////

class UslovSaInace : public Naredba {
public:
    UslovSaInace(Izraz* i, Naredba* n1, Naredba* n2)
        : izraz_(i), n1_(n1), n2_(n2) {}

    ~UslovSaInace() override {
        delete izraz_;
        delete n1_;
        delete n2_;
    }

    UslovSaInace(const UslovSaInace&) = delete;
    UslovSaInace& operator=(const UslovSaInace&) = delete;

    void izvrsi() const override;
private:
    Izraz* izraz_;
    Naredba* n1_;
    Naredba* n2_;
};

////////////////////////////////////////////////////////////

class UslovBezInace : public Naredba {
public:
    UslovBezInace(Izraz* i, Naredba* n)
        : izraz_(i), n_(n) {}

    ~UslovBezInace() override {
        delete izraz_;
        delete n_;
    }

    UslovBezInace(const UslovBezInace&) = delete;
    UslovBezInace& operator=(const UslovBezInace&) = delete;

    void izvrsi() const override;
private:
    Izraz* izraz_;
    Naredba* n_;
};

////////////////////////////////////////////////////////////

class Petlja : public Naredba {
public:
    Petlja(Izraz* i, Naredba* n)
        : izraz_(i), naredba_(n) {}

    ~Petlja() override {
        delete izraz_;
        delete naredba_;
    }

    Petlja(const Petlja&) = delete;
    Petlja& operator=(const Petlja&) = delete;
    
    void izvrsi() const override;
private:
    Izraz* izraz_;
    Naredba* naredba_;
};