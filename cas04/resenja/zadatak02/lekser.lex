%option noyywrap
%option noinput
%option nounput

%{

#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

%}

%%

[0-9]+                      { return broj; }

[()+*]                      { return *yytext; }

[ \t\n]                     { }

.                           {
    fprintf(stderr, "Leksicka greska: %s\n", yytext);
    exit(EXIT_FAILURE);
}

%%
