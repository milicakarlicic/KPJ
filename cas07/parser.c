#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

/*
---------------------------------------------------------------------------

E ->  E - T
    | T
T ->  T * F
    | F
F ->  (E)
    | broj

---------------------------------------------------------------------------

Pored sintaksne analize aritmetickih izraza racunamo i njihovu vrijednost:

                                                SHEMA PREVODJENJA

E ->  TE'                        E ->  T{E'.ulaz = T.izlaz}E'{E.izlaz = E'.izlaz}
E'->  -TE'                       E'->  -T{E'.ulaz = E'.ulaz - T.izlaz}E'{E'.izlaz = E'.izlaz}
     | eps                       E'->  eps{E'.izlaz = E'.ulaz}
T ->  FT'                        T ->  F{T'.ulaz = F.izlaz}T'{T.izlaz = T'.izlaz}
T'->  *FT'                       T'->  *F{T'.ulaz = T'.ulaz * F.izlaz}T'{T'.izlaz = T'.izlaz}
     | eps                       T'->  eps{T'.izlaz = T'.ulaz}
F ->  (E)                        F ->  (E){F.izlaz = E.izlaz}
    | broj                       F ->  broj{F.izlaz = broj.izlaz}

---------------------------------------------------------------------------
*/

extern int yylex();

int preduvid;

int yylval;

void greska(char *poruka) {
    fprintf(stderr, "Sintaksna greska: %s\n", poruka);
    exit(EXIT_FAILURE);
}

int E();
int EP(int ulaz);
int T();
int TP(int ulaz);
int F();

int main() {
    preduvid = yylex();

    int rezultat = E();

    if(preduvid == eoi) {
        printf("PRIPADA: %d\n", rezultat);
    } else {
        printf("NE PRIPADA\n");
    }

    return 0;
}

int E() {
    if(preduvid == '(' || preduvid == broj) {
        printf("E -> TE'\n");
        return EP(T());
    } else {
        greska("[E] Ocekivano ( ili broj na ulazu");
        return -1;
    }
}

int EP(int ulaz) {
    if(preduvid == '-') {
        printf("E' -> -TE'\n");
        preduvid = yylex();
        return EP(ulaz-T());
    } else if(preduvid == eoi || preduvid == ')') {
        printf("E' -> eps\n");
        return ulaz;
    } else {
        greska("[E'] Ocekivano -, eoi ili ) na ulazu");
        return -1;
    }
}

int T() {
    if(preduvid == '(' || preduvid == broj) {
        printf("T -> FT'\n");
        return TP(F());
    } else {
        greska("[T] Ocekivano (, broj na ulazu");
        return -1;
    }
}

int TP(int ulaz) {
    if(preduvid == '*') {
        printf("T' -> *FT'\n");
        preduvid = yylex();
        return TP(ulaz * F());
    } else if(preduvid == eoi || preduvid == ')' || preduvid == '-') {
        printf("T' -> eps\n");
        return ulaz;
    } else {
        greska("[T'] Ocekivano -, *, eoi ili ) na ulazu");
        return -1;
    }
}

int F() {
    if(preduvid == '(') {
        printf("F -> (E)\n");
        preduvid = yylex();

        int pom = E();

        if(preduvid != ')')
            greska("[F] Ocekivana ) na ulazu");
        preduvid = yylex();
        return pom;
    } else if(preduvid == broj) {
        printf("F -> broj\n");
        preduvid = yylex();
        return yylval;
    } else {
        greska("[F] Ocekivano ( ili broj na ulazu");
        return -1;
    }
}
