%option noyywrap
%option noinput
%option nounput

/*
    ● flex - program za generisanje leksickog analizatora (info flex dokumentacija)
    ● pisemo skripte sa ekstenzijom .lex
    ● pozivanje i pokretanje programa:
        ○ flex naziv_fajla.lex (flex izgenerise fajl lex.yy.c)
        ○ gcc lex.yy.c -Wall -Wextra
        ○ ./a.out
    ● program koji pisemo se sastoji iz tri dijela razvdojena %%:
        ○ sekcija za definicije (sadrzi podsekciju %{....%} u okviru koje pisemo C-kod koji se umece pri pocetku fajla lex.yy.c)
        ○ sekcija za pravila (regularni izrazi kojima pridruzujemo odgovarajuce akcije)
        ○ sekcija za korisnicki kod (umece se na kraj fajla lex.yy.c)
    ● bitna svojstva flex-a:
        ○ pravila cita redom
        ○ ulazi u akciju regularnog izraza koji je najvise karaktera poklopio (ako ima vise takvih ulazi se u akciju koja odgovara prvom od njih)
    ● bitne promenljive i funkcije iz fajla lex.yy.c:
        ○ yylex - funkcija koja radi leksicku analizu (cita leksemu sa ulaza i pridruzuje joj token)
        ○ yytext - promenljiva u kojoj se cuva procitana leksema
        ○ yyin - promenljiva u kojoj se cuva ulaz sa kojeg yylex cita lekseme (podrazumijevano stdin)
        ○ yyout - promenljiva u kojoj se cuva izlaz na koji yylex pise (podrazumijevano stdout)
*/

%{

#include <stdio.h>
#include <stdlib.h>

#define broj    1

%}

%%

[0-9]+          { return broj; }

[-/+*()]        { return *yytext; }

[ \t]           {}

.               {
    // Zasto je greska napisati .* ili .+?
    fprintf(stderr, "Leksicka greska: nepoznat karakter %c\n", *yytext);
    exit(EXIT_FAILURE);
}

%%

int main() {
    int token;

    // Citamo tokene sve dok ne dodjemo do kraja ulaza tj. dok funkcija yylex ne vrati 0
    while ((token = yylex()) != 0) {
        if (token == broj) {
            printf("broj");
        } else {
            printf("%c", token);
        }
    }
    
    printf("\n");

    return 0;
}
