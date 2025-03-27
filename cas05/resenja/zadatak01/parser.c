#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tokeni.h"

#define MAX 256

/*
----------------------------------------------------------------------
    NIZ_NAREDBI ->  NIZ_NAREDBI NAREDBA ;
                 | NAREDBA ;
    NAREDBA ->  DEKLARACIJA
              | stampaj E
    DEKLARACIJA ->  sifra id
                  | sifra id(broj, broj)
                  | sifra id = E
    E ->  E + F
        | E - F
        | F
    F ->  (E)
        | broj
        | id
----------------------------------------------------------------------
    NIZ_NAREDBI ->  NAREDBA ; NIZ_NAREDBI'    {sifra, stampaj}
    NIZ_NAREDBI' ->  NAREDBA ; NIZ_NAREDBI'   {sifra, stampaj}
                  | eps                     {eoi}
    NAREDBA ->  DEKLARACIJA                 {sifra}
              | stampaj E                   {stampaj}
    DEKLARACIJA ->  sifra id DEKLARACIJA'   {sifra}
    DEKLARACIJA' ->  eps                    {;}
                   | (broj, broj)           {(}
                   | = E                    {=}
    E ->  FE'                               {(, broj, id}
    E' ->  +FE'                             {+}
         | -FE'                             {-}
         | eps                              {;, )}
    F ->  (E)                               {(}
        | broj                              {broj}
        | id                                {id}
----------------------------------------------------------------------
*/

extern int yylex();

void greska(char *poruka) {
    fprintf(stderr, "Sintaksna greska: %s\n", poruka);
    exit(EXIT_FAILURE);
}

int preduvid;

int stek[MAX];

int sp;

void stavi_na_stek(int element);
int skini_sa_steka();
bool pun();
bool prazan();

int main() {
    preduvid = yylex();

    stavi_na_stek(NIZ_NAREDBI);

    while(!prazan()) {
        int element = skini_sa_steka();

        switch(element) {
            case NIZ_NAREDBI:
                if(preduvid == stampaj || preduvid == sifra) {
                    printf("NIZ_NAREDBI -> NAREDBA ; NIZ_NAREDBI'\n");
                    stavi_na_stek(NIZ_NAREDBI_P);
                    stavi_na_stek(';');
                    stavi_na_stek(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI] Ocekivano stampaj ili sifra na ulazu");
                }
                break;
            case NIZ_NAREDBI_P:
                if(preduvid == sifra || preduvid == stampaj) {
                    printf("NIZ_NAREDBI' -> NAREDBA ; NIZ_NAREDBI'\n");
                    stavi_na_stek(NIZ_NAREDBI_P);
                    stavi_na_stek(';');
                    stavi_na_stek(NAREDBA);
                } else if(preduvid == eoi) {
                    printf("NIZ_NAREDBI' -> eps\n");
                } else {
                    greska("[NIZ_NAREDBI'] Ocekivano sifra, stampaj ili eoi na ulazu");
                }
                break;
            case NAREDBA:
                if(preduvid == sifra) {
                    printf("NAREDBA -> DEKLARACIJA\n");
                    stavi_na_stek(DEKLARACIJA);
                } else if(preduvid == stampaj) {
                    printf("NAREDBA -> stampaj E\n");
                    stavi_na_stek(E);
                    stavi_na_stek(stampaj);
                } else {
                    greska("[NAREDBA] Ocekivano sifra ili stampaj na ulazu");
                }
                break;
            case DEKLARACIJA:
                if(preduvid == sifra) {
                    printf("DEKLARACIJA -> sifra id DEKLARACIJA_P\n");
                    stavi_na_stek(DEKLARACIJA_P);
                    stavi_na_stek(id);
                    stavi_na_stek(sifra);
                } else {
                    greska("[DEKLARACIJA] Ocekivano sifra na ulazu");
                }
                break;
            case DEKLARACIJA_P:
                if(preduvid == ';') {
                    printf("DEKLARACIJA' -> eps\n");
                } else if(preduvid == '(') {
                    printf("DEKLARACIJA' -> (broj, broj)\n");
                    stavi_na_stek(')');
                    stavi_na_stek(broj);
                    stavi_na_stek(',');
                    stavi_na_stek(broj);
                    stavi_na_stek('(');
                } else if(preduvid == '=') {
                    printf("DEKLARACIJA' -> = E\n");
                    stavi_na_stek(E);
                    stavi_na_stek('=');
                } else {
                    greska("[DEKLARACIJA'] Ocekivano ;, ( ili = na ulazu");
                }
                break;
            case E:
                if(preduvid == '(' || preduvid == broj || preduvid == id) {
                    printf("E -> FE'\n");
                    stavi_na_stek(EP);
                    stavi_na_stek(F);
                } else {
                    greska("[E] Ocekivano (, broj ili id na ulazu");
                }
                break;
            case EP:
                if(preduvid == '+') {
                    printf("E' -> +FE'\n");
                    stavi_na_stek(EP);
                    stavi_na_stek(F);
                    stavi_na_stek('+');
                } else if(preduvid == '-') {
                    printf("E' -> -FE'\n");
                    stavi_na_stek(EP);
                    stavi_na_stek(F);
                    stavi_na_stek('-');
                } else if(preduvid == ';' || preduvid == ')') {
                    printf("E' -> eps\n");
                } else {
                    greska("[E'] Ocekivano na ulazu +, -, ; ili ) na ulazu");
                }
                break;
            case F:
                if(preduvid == '(') {
                    printf("F -> (E)\n");
                    stavi_na_stek(')');
                    stavi_na_stek(E);
                    stavi_na_stek('(');
                } else if(preduvid == broj) {
                     printf("F -> broj\n");
                     stavi_na_stek(broj);
                } else if(preduvid == id) {
                     printf("F -> id\n");
                     stavi_na_stek(id);
                } else {
                    greska("[F] Ocekivano (, broj ili id na ulazu");
                }
                break;
            default:
                if(preduvid == element) {
                    preduvid = yylex();
                } else {
                    greska("Napoklapanje tokena na ulazu i steku");
                }
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
