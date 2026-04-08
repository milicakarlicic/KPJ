#include <iostream>

/*

  Implementacija sintaksnog analizatora za gramatiku:
  
            skupovi izbora:

  S ->  aA      {a}
      | bB      {b}
  A ->  aB      {a}
      | C       {c}
  B ->  bA      {b}
      | cB      {c}
  C ->  c       {c}

*/

extern int yylex();

void greska(std::string poruka) {
    std::cerr << "Sintaksna greska: " << poruka << std::endl;
    exit(EXIT_FAILURE);
}

int token;

void S();
void A();
void B();
void C();

int main() {
    token = yylex();

    S();

    if (token == 0) {
        std::cout << "Recenica pripada gramatici" << std::endl;
    } else {
        std::cout << "Recenica NE pripada gramatici" << std::endl;
    }
}

void S() {
    if (token == 'a') {
        std::cout << "S -> a A\n";
        token = yylex();
        A();
    } else if (token == 'b') {
        std::cout << "S -> b B\n";
        token = yylex();
        B();
    } else {
        greska("[S]: Ocekivani tokeni a ili b");
    }
}

void A() {
    if (token == 'a') {
        std::cout << "A -> a B\n";
        token = yylex();
        B();
    } else if (token == 'c') {
        std::cout << "A -> C\n";
        C();
    } else {
        greska("[A] Ocekivani tokeni a ili c");
    }
}

void B() {
    if (token == 'b') {
        std::cout << "B -> b A\n";
        token = yylex();
        A();
    } else if (token == 'c') {
        std::cout << "B -> c B\n";
        token = yylex();
        B();
    } else {
        greska("[B] Ocekivani tokeni b ili c");
    }
}

void C() {
    if (token == 'c') {
        std::cout << "C -> c\n"; 
        token = yylex();
    } else {
        greska("[C] Ocekivan token c");
    }
}