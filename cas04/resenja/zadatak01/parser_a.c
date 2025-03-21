#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

/*
----------------------------------------------------------------------

Sintaksna analiza nanize - koraci:

    1. naivna gramatika
    2. oslobadjanje lijevo faktorisanih i lijevo rekurzivnih pravila
    3. racunanje skupova izbora
    4. implementacija

----------------------------------------------------------------------

Naivna gramatika:

    NIZ_NAREDBI ->  NIZ_NAREDBI NAREDBA
                 | NAREDBA
    NAREDBA ->  int_token id = E ;
              | print_token ( E ) ;
    E ->  E '|' T
        | T
    T ->  T & G
        | G
    G ->  ~G
        | F
    F ->  (E)
        | broj
        | id

----------------------------------------------------------------------

Transformisana gramatika sa izracunatim skupovima izbora:

    NIZ_NAREDBI ->  NAREDBA NIZ_NAREDBI'    {int_token, print_token}
    NIZ_NAREDBI' ->  NAREDBA NIZ_NAREDBI'   {int_token, print_token}
                  | eps                     {eoi}
    NAREDBA ->  int_token id = E ;          {int_token}
              | print_token ( E ) ;         {print_token}
    E ->  T E'                              {~, (, broj, id}
    E' ->  '|' T E'                         {|}
          | eps                             {;, )}
    T ->  G T'                              {~, (, broj, id)}
    T' ->  & G T'                           {&}
         | eps                              {;, ), |}
    G ->  ~G                                {~}
        | F                                 {(, broj, id)}
    F ->  (E)                               {(}
        | broj                              {broj}
        | id                                {id}

----------------------------------------------------------------------
*/

extern int yylex();

int preduvid;

void greska(char *poruka) {
    fprintf(stderr, "Sintaksna greska: %s\n", poruka);
    exit(EXIT_FAILURE);
}

void NIZ_NAREDBI();
void NIZ_NAREDBI_P();
void NAREDBA();
void E();
void EP();
void T();
void TP();
void G();
void F();

int main() {
    preduvid = yylex();

    NIZ_NAREDBI();
    
    if(preduvid == eoi) {
        printf("Recenica pripada gramatici\n");
    } else {
        printf("Recenica NE pripada gramatici\n");
    }
}

void NIZ_NAREDBI() {
    if(preduvid == int_token || preduvid == print_token) {
        printf("NIZ_NAREDBI -> NAREDBA NIZ_NAREDBI'\n");
        NAREDBA();
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI] Ocekivano int_token ili print_token na ulazu");
    }
}

void NIZ_NAREDBI_P() {
    if(preduvid == int_token || preduvid == print_token) {
        printf("NIZ_NAREDBI' -> NAREDBA NIZ_NAREDBI'\n");
        NAREDBA();
        NIZ_NAREDBI_P();
    } else if(preduvid == eoi) {
        printf("NIZ_NAREDBI' -> eps\n");
    } else {
        greska("[NIZ_NAREDBI'] Ocekivano int_token, eoi ili print_token na ulazu");
    }
}

void NAREDBA() {
    if(preduvid == int_token) {
        printf("NAREDBA -> int_token id = E ;\n");
        preduvid = yylex();
        if(preduvid != id)
            greska("[NAREDBA] Ocekivano id na ulazu");
        preduvid = yylex();
        if(preduvid != '=')
            greska("[NAREDBA] Ocekivano = na ulazu");
        preduvid = yylex();
        E();
        if(preduvid != ';')
            greska("[NAREDBA] Ocekivano ; na ulazu");
        preduvid = yylex();
    } else if(preduvid == print_token) {
        printf("NAREDBA -> print_token ( E ) ;\n");
        preduvid = yylex();
        if(preduvid != '(')
            greska("[NAREDBA] Ocekivano ( na ulazu");
        preduvid = yylex();
        E();
        if(preduvid != ')')
            greska("[NAREDBA] Ocekivano ) na ulazu");
        preduvid = yylex();
        if(preduvid != ';')
            greska("[NAREDBA] Ocekivano ; na ulazu");
        preduvid = yylex();
    } else {
        greska("[NAREDBA] Ocekivano int_token ili print_token na ulazu");
    }
}

void E() {
    if(preduvid == '~' || preduvid == '(' || preduvid == broj || preduvid == id) {
        printf("E -> T E'\n");
        T();
        EP();
    } else {
        greska("[E] Ocekivano ~, (, broj ili id na ulazu");
    }
}

void EP() {
    if(preduvid == '|') {
        printf("E' -> | T E'\n");
        preduvid = yylex();
        T();
        EP();
    } else if(preduvid == ';' || preduvid == ')') {
        printf("E' -> eps\n");
    } else {
        greska("[E'] Ocekivano |, ; ili ) na ulazu");
    }
}

void T() {
    if(preduvid == '~' || preduvid == '(' || preduvid == broj || preduvid == id) {
        printf("T -> G T'\n");
        G();
        TP();
    } else {
        greska("[T] Ocekivano ~, (, broj ili id na ulazu");
    }
}

void TP() {
    if(preduvid == '&') {
        printf("T' -> | G T'\n");
        preduvid = yylex();
        G();
        TP();
    } else if(preduvid == ';' || preduvid == ')' || preduvid == '|') {
        printf("T' -> eps\n");
    } else {
        greska("[T'] Ocekivano &, |, ; ili ) na ulazu");
    }
}

void G() {
    if(preduvid == '~') {
        printf("G -> ~ G\n");
        preduvid = yylex();
        G();
    } else if(preduvid == '(' || preduvid == broj || preduvid == id) {
        printf("G -> F\n");
        F();
    } else {
        greska("[G] Ocekivano ~, (, broj ili id na ulazu");
    }
}

void F() {
    if(preduvid == '(') {
        printf("F -> ( E )\n");
        preduvid = yylex();
        E();
        if(preduvid != ')')
            greska("[F] Ocekivano ) na ulazu");
        preduvid = yylex();
    } else if(preduvid == broj) {
        printf("F -> broj\n");
        preduvid = yylex();
    } else if(preduvid == id) {
        printf("F -> id\n");
        preduvid = yylex();
    } else {
        greska("[F] Ocekivano (, broj ili id na ulazu");
    }
}
