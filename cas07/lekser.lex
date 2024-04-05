%option noyywrap
%option noinput
%option nounput

%{

#include <stdio.h>
#include <stdlib.h>

#include "tokeni.h"

extern int yylval;

%}

%%

[0-9]+          {
// "123" --> 123
    yylval = atoi(yytext);
    return broj;
}

[-*()]          { return *yytext; }

[ \t]           {}

\n              { return eoi; }

.               {
    fprintf(stderr, "Leksicka greska: %s\n", yytext);
    exit(EXIT_FAILURE);
}

%%
