#include <stdio.h>
#include <stdlib.h>

/*

  Implementacija sintaksnog analizatora za gramatiku:
  
  S ->  aA      {a}
      | bB      {b}
  A ->  aB      {a}
      | C       {c}
  B ->  bA      {b}
      | cB      {c}
  C ->  c       {c}

*/

extern int yylex();

int token;

void greska(char *poruka) {
    fprintf(stderr, "Sintaksna greska: %s\n", poruka);
    exit(EXIT_FAILURE);
}

void S();
void A();
void B();
void C();

void S() {
    if (token == 'a') {
        printf("S -> a A\n");
        // kako prepoznajemo terminale? ucitavamo novi token sa ulaza
        // kako prepoznajemo neterminale? pozivamo odgovarajucu funkciju
        token = yylex();
        A();
    } else if (token == 'b') {
        printf("S -> b B\n");
        token = yylex();
        B();
    } else {
        greska("[S] Ocekivano a ili b na ulazu");
    }
}

void A() {
    if (token == 'a') {
        printf("A -> a B\n");
        token = yylex();
        B();
    } else if (token == 'c') {
        printf("A -> C\n");
        C();
    } else {
        greska("[A] Ocekivano a ili c na ulazu");
    }
}

void B() {
    if (token == 'b') {
        printf("B -> b A\n");
        token = yylex();
        A();
    } else if (token == 'c') {
        printf("B -> c B\n");
        token = yylex();
        B();
    } else {
        greska("[B] Ocekivano c ili b na ulazu");
    }
}

void C() {
    if (token == 'c') {
        printf("C -> c\n");
        token = yylex();
    } else {
        greska("[C] Ocekivano c  na ulazu");
    }
}

int main() {
    token = yylex();
    
    S();
    
    if (token == 0) {
        printf("Recenica pripada gramatici\n");
    } else {
        printf("Recenica NE pripada gramatici\n");
    }

    return 0;
}
