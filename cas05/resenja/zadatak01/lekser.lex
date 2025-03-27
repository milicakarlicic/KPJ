%option noyywrap
%option noinput
%option nounput

%{

#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

%}

%%

sifra                   { return sifra; }

stampaj                 { return stampaj; }

[a-zA-Z_][a-zA-Z_0-9]*  { return id; }

[0-9]+([.][0-9]+)?      { return broj; }

[();=\-,+]              { return *yytext; }

[ \t\n]                 {}

.                       {
    fprintf(stderr, "Leksicka greska: %s\n", yytext);
    exit(EXIT_FAILURE);
}

%%
