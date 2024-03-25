%option noyywrap
%option nounput
%option noinput

%{

#include <stdio.h>
#include <stdlib.h>
#include "tokeni.h"

%}

%%

"int"                               { return int_token; }

"print"                             { return print_token; }

[a-zA-Z_][a-zA-Z_0-9]*              { return id; }

0|[1-9][0-9]*                       { return broj; }

0(0|[1-7][0-7]*)                    { return broj; }

0x(0|[1-9a-fA-F][0-9a-fA-F]*)       { return broj; }

[=;&|~()]                           { return *yytext; }

[ \t\n]                             { }

.                                   {
    fprintf(stderr, "Leksicka greska: %s\n", yytext);
    exit(EXIT_FAILURE);
}

%%
