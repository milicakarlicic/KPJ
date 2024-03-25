#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

#define YYDEBUG 

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
#ifdef YYDEBUG
        printf("NIZ_NAREDBI => NAREDBA ; NIZ_NAREDBI'\n");
#endif
        NAREDBA();
        if(preduvid != ';')
            greska("[NIZ_NAREDBI] Ocekivano ; na ulazu");
        preduvid = yylex();
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI] Ocekivano int_token ili print_token na ulazu");
    }
}

void NIZ_NAREDBI_P() {
    if(preduvid == int_token || preduvid == print_token) {
#ifdef YYDEBUG
        printf("NIZ_NAREDBI' => NIZ_NAREDBI\n");
#endif
        NIZ_NAREDBI();
    } else if(preduvid == eoi) {
#ifdef YYDEBUG
        printf("NIZ_NAREDBI' => eps\n");
#endif
    } else {
        greska("[NIZ_NAREDBI'] Ocekivano eoi, int_token ili print_token na ulazu");
    }
}

void NAREDBA() {
    if(preduvid == int_token) {
#ifdef YYDEBUG
        printf("NAREDBA => int_token id = E\n");
#endif
        preduvid = yylex();
        if(preduvid != id)
            greska("[NAREDBA] Ocekivano id na ulazu");
        preduvid = yylex();
        if(preduvid != '=')
            greska("[NAREDBA] Ocekivano = na ulazu");
        preduvid = yylex();
        E();
    } else if(preduvid == print_token) {
#ifdef YYDEBUG
        printf("NAREDBA => print_token ( E )\n");
#endif
        preduvid = yylex();
        if(preduvid != '(')
            greska("[NAREDBA] Ocekivano ( na ulazu");
        preduvid = yylex();
        E();
        if(preduvid != ')')
            greska("[NAREDBA] Ocekivano ) na ulazu");
        preduvid = yylex();
    } else {
        greska("[NAREDBA] Ocekivano int_token ili print_token na ulazu");
    }
}

void E() {
    if(preduvid == '~' || preduvid == '(' || preduvid == broj || preduvid == id) {
#ifdef YYDEBUG
        printf("E => T E'\n");
#endif
        T();
        EP();
    } else {
        greska("[E] Ocekivano ~, (, broj ili id na ulazu");
    }
}

void EP() {
    if(preduvid == '|') {
#ifdef YYDEBUG
        printf("E' => | T E'\n");
#endif
        preduvid = yylex();
        T();
        EP();
    } else if(preduvid == ';' || preduvid == ')') {
#ifdef YYDEBUG
        printf("E' => eps\n");
#endif
    } else {
        greska("[E'] Ocekivano |, ; ili ) na ulazu");
    }
}

void T() {
    if(preduvid == '~' || preduvid == '(' || preduvid == broj || preduvid == id) {
#ifdef YYDEBUG
        printf("T => G T'\n");
#endif
        G();
        TP();
    } else {
        greska("[T] Ocekivano ~, (, broj ili id na ulazu");
    }
}

void TP() {
    if(preduvid == '&') {
#ifdef YYDEBUG
        printf("T' => & G T'\n");
#endif
        preduvid = yylex();
        G();
        TP();
    } else if(preduvid == ';' || preduvid == ')' || preduvid == '|') {
#ifdef YYDEBUG
        printf("T' => eps\n");
#endif
    } else {
        greska("[T'] Ocekivano &, |, ; ili ) na ulazu");
    }
}

void G() {
    if(preduvid == '~') {
#ifdef YYDEBUG
        printf("G => ~ G\n");
#endif
        preduvid = yylex();
        G();
    } else if(preduvid == '(' || preduvid == broj || preduvid == id) {
#ifdef YYDEBUG
        printf("G => F\n");
#endif
        F();
    } else {
        greska("[G] Ocekivano ~, (, broj ili id na ulazu");
    }
}

void F() {
    if(preduvid == '(') {
#ifdef YYDEBUG
        printf("F => ( E )\n");
#endif
        preduvid = yylex();
        E();
        if(preduvid != ')')
            greska("[F] Ocekivano ) na ulazu");
        preduvid = yylex();
    } else if(preduvid == broj) {
#ifdef YYDEBUG
        printf("F => broj\n");
#endif
        preduvid = yylex();
    } else if(preduvid == id) {
#ifdef YYDEBUG
        printf("F => id\n");
#endif
        preduvid = yylex();
    } else {
        greska("[F] Ocekivano (, broj ili id na ulazu");
    }
}
