#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokeni.h"

#define YYDEBUG 

#define MAX 	256

extern int yylex();

int preduvid;

void greska(char *poruka) {
    fprintf(stderr, "Sintaksna greska: %s\n", poruka);
    exit(EXIT_FAILURE);
}

int stek[MAX];

int sp;

void stavi_na_stek(int element);
int skini_sa_steka();
bool pun();
bool prazan();

int main() {
    preduvid = yylex();

    stavi_na_stek(E);

    while(!prazan()) {
        int element = skini_sa_steka();

        switch(element) {
            case E:
                if(preduvid == broj || preduvid == '(') {
#ifdef YYDEBUG
                    printf("E -> TE'\n");
#endif
                    stavi_na_stek(EP);
                    stavi_na_stek(T);
                } else {
                    greska("[E] Ocekivano broj ili ( na ulazu\n");
                }
                break;
            case EP:
                if(preduvid == '+') {
#ifdef YYDEBUG
                    printf("E' -> +TE'\n");
#endif
                    stavi_na_stek(EP);
                    stavi_na_stek(T);
                    stavi_na_stek('+');
                } else if(preduvid == ')' || preduvid == eoi) {
#ifdef YYDEBUG
                    printf("E' -> eps\n");
#endif
                } else {
                    greska("[E'] Ocekivano +, ) ili eoi na ulazu");
                }
                break;
            case T:
                if(preduvid == '(' || preduvid == broj) {
#ifdef YYDEBUG
                    printf("T -> FT'\n");
#endif
                    stavi_na_stek(TP);
                    stavi_na_stek(F);
                } else {
                    greska("[T] Ocekivano ( ili broj na ulazu");
                }
                break;
            case TP:
                if(preduvid == '*') {
#ifdef YYDEBUG
                    printf("T' -> *FT'\n");
#endif
                    stavi_na_stek(TP);
                    stavi_na_stek(F);
                    stavi_na_stek('*');
                } else if(preduvid == ')' || preduvid == eoi || preduvid == '+') {
#ifdef YYDEBUG
                    printf("T' -> eps\n");
#endif
                } else {
                    greska("[T'] Ocekivano *, ), eoi ili + na ulazu");
                }
                break;
            case F:
                if(preduvid == '(') {
#ifdef YYDEBUG
                    printf("F -> (E)\n");
#endif
                    stavi_na_stek(')');
                    stavi_na_stek(E);
                    stavi_na_stek('(');
                } else if(preduvid == broj) {
#ifdef YYDEBUG
                    printf("F -> broj\n");
#endif
                    stavi_na_stek(broj);
                } else {
                    greska("[F] Ocekivano ( ili broj na ulazu");
                }
                break;
            default:
                if(preduvid != element)
                    greska("Napoklapanje tokena na steku i ulazu");
                preduvid = yylex();
        }
    }

    if(preduvid == eoi)
        printf("Recenica pripada gramatici\n");
    else
        printf("Recenica NE pripada gramatici\n");

    return 0;
}

void stavi_na_stek(int element) {
    if(pun()) {
        fprintf(stderr, "Pun\n");
        exit(EXIT_FAILURE);
    }

    stek[sp++] = element;
}

int skini_sa_steka() {
    if(prazan()) {
        fprintf(stderr, "Prazan\n");
        exit(EXIT_FAILURE);
    }

    return stek[--sp];
}

bool pun() {
    return sp == MAX;
}

bool prazan() {
    return sp == 0;
}
