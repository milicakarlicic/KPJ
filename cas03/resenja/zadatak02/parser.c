#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

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

  E ->  TE'	  {broj, (}
  E'->  +TE'	  {+}
      | eps	  {), eoi}
  T ->  FT'	  {broj, (}
  T'->  *FT'	  {*}
      | eps	  {), eoi, +}
  F ->  (E)	  {(}
      | broj	  {broj}
---------------------------------------------
*/

extern int yylex();

int preduvid;

void greska(char *poruka) {
    fprintf(stderr, "Sintaksna greska: %s\n", poruka);
    exit(EXIT_FAILURE);
}

void E();
void EP();
void T();
void TP();
void F();

void E() {
    if(preduvid == broj || preduvid == '(') {
        printf("E -> TE'\n");
        T();
        EP();
    } else {
        greska("[E] Ocekivano broj ili ( na ulazu");
    }
}

void EP() {
    if(preduvid == '+') {
        printf("E' -> +TE'\n");
        preduvid = yylex();
        T();
        EP();
    } else if(preduvid == ')' || preduvid == eoi) {
        printf("E' -> eps\n");
    } else {
        greska("[E'] Ocekivano +, eoi ili ) na ulazu");
    }
}

void T() {
    if(preduvid == broj || preduvid == '(') {
        printf("T -> FT'\n");
        F();
        TP();
    } else {
        greska("[T] Ocekivano broj ili ( na ulazu");
    }
}

void TP() {
    if(preduvid == '*') {
        printf("T' -> *FT'\n");
        preduvid = yylex();
        F();
        TP();
    } else if(preduvid == ')' || preduvid == eoi || preduvid == '+') {
        printf("T' -> eps\n");
    } else {
        greska("[T'] Ocekivano +, *, eoi ili ) na ulazu");
    }
}

void F() {
    if(preduvid == '(') {
        printf("F -> (E)\n");
        preduvid = yylex();
        E();
        // Zasto je vazan uslov? Recenica koja bi u slucaju da nije napisan bila prihvacena 1 + (2 + 3
        if(preduvid != ')') {
            greska("[F] Ocekivana ) na ulazu");
        }
        preduvid = yylex();
    } else if(preduvid == broj) {
        printf("F -> broj\n");
        preduvid = yylex();
    } else {
        greska("[F] Ocekivan broj ili ( na ulazu");
    }
}

int main() {
    preduvid = yylex();

    E();

    if(preduvid == eoi) {
        printf("Recenica pripada gramatici\n");
    } else {
        printf("Recenica NE pripada gramatici\n");
    }

    return 0;
}
