#include <iostream>
#include "tokeni.hpp"

extern int yylex();

void greska(std::string poruka) {
    std::cerr << "Sintaksna greska: " << poruka << std::endl;
    exit(EXIT_FAILURE);
}

int preduvid;

/*
---------------------------------------------
  Rekurzivni spust za gramatiku:
  
  E ->  E+T
      | T
  T ->  T*F
      | F
  F ->  (E)
      | broj
---------------------------------------------
		skupovi izbora:

  E ->  TE'	      {broj, (}
  E'->  +TE'	  {+}
      | eps	      {), eoi}
  T ->  FT'	      {broj, (}
  T'->  *FT'	  {*}
      | eps	      {), eoi, +}
  F ->  (E)	      {(}
      | broj	  {broj}
---------------------------------------------
*/

void E();
void EP();
void T();
void TP();
void F();

int main() {
    preduvid = yylex();

    E();

    if (preduvid == eoi) {
        std::cout << "Recenica pripada gramatici" << std::endl;
    } else {
        std::cout << "Recenica NE pripada gramatici" << std::endl;
    }

    return 0;
}

void E() {
    if (preduvid == '(' || preduvid == broj) {
        std::cout << "E -> T E'\n";
        T();
        EP();
    } else {
        greska("[E] Ocekivani tokeni ( ili broj");
    }
}

void EP() {
    if (preduvid == '+') {
        std::cout << "E' -> + T E'\n";
        preduvid = yylex();
        T();
        EP();
    } else if (preduvid == ')' || preduvid == eoi) {
        std::cout << "E' -> Eps\n";
    } else {
        greska("[EP] Ocekivani tokeni +, ), eoi");
    }
}

void T() {
    if (preduvid == '(' || preduvid == broj) {
        std::cout << "T -> F T'\n";
        F();
        TP();
    } else {
        greska("[T] Ocekivani tokeni ( ili broj");
    }
}

void TP() {
if (preduvid == '*') {
        std::cout << "T' -> * F T'\n";
        preduvid = yylex();
        F();
        TP();
    } else if (preduvid == '+' || preduvid == ')' || preduvid == eoi) {
        std::cout << "T' -> Eps\n";
    } else {
        greska("[TP] Ocekivani tokeni *, +, ), eoi");
    }
}

void F() {
    if (preduvid == '(') {
        std::cout << "F -> ( E )\n";
        preduvid = yylex();
        E();
        if (preduvid != ')') {
            greska("[F] Ocekivana )");
        }
        preduvid = yylex();
    } else if (preduvid == broj) {
        std::cout << "F -> broj\n";
        preduvid = yylex();
    } else {
        greska("[F] Ocekivani tokeni ( ili broj");
    }
}