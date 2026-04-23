#include <iostream>
#include <stack>
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

int main() {
    preduvid = yylex();

    std::stack<int> stek;

    stek.push(E);
    while (!stek.empty()) {
        int element = stek.top();
        stek.pop();

        switch (element) {  
            case E:
                if (preduvid == broj || preduvid == '(') {
                    std::cout << "E -> TE'" << std::endl;
                    stek.push(EP);
                    stek.push(T);
                } else {
                    greska("Ocekivani tokeni broj ili (");
                }
                break;
            case EP:
                if (preduvid == '+') {
                    std::cout << "E' -> +TE'" << std::endl;
                    stek.push(EP);
                    stek.push(T);
                    stek.push('+');
                } else if (preduvid == ')' || preduvid == eoi) {
                    std::cout << "E' -> eps" << std::endl;
                } else {
                    greska("Ocekivani tokeni +, ) ili eoi");
                }
                break;
            case T:
                if (preduvid == broj || preduvid == '(') {
                    std::cout << "T -> FT'" << std::endl;
                    stek.push(TP);
                    stek.push(F);
                } else {
                    greska("Ocekivani tokeni broj ili (");  
                }
                break;
            case TP:
                if (preduvid == '*') {
                    std::cout << "T' -> *FT'" << std::endl;
                    stek.push(TP);
                    stek.push(F);
                    stek.push('*');
                } else if (preduvid == ')' || preduvid == eoi || preduvid == '+') {
                    std::cout << "T' -> eps" << std::endl;
                } else {
                    greska("Ocekivani tokeni *, ), eoi ili +");
                }
                break;
            case F:
                if (preduvid == '(') {
                    std::cout << "F -> (E)" << std::endl;
                    stek.push(')');
                    stek.push(E);
                    stek.push('(');
                } else if (preduvid == broj) {
                    std::cout << "F -> broj" << std::endl;
                    stek.push(broj);
                } else {
                    greska("Ocekivani tokeni ( ili broj");
                }
                break;
            default:
                if (element != preduvid) {
                    greska("Nepoklapanje tokena na steku i ulazu!");
                }
                preduvid = yylex();
        }
    }

    if (preduvid == eoi) {
        std::cout << "Recenica pripada gramatici" << std::endl;
    } else {
        std::cout << "Recenica NE pripada gramatici" << std::endl;
    }

    return 0;
}
