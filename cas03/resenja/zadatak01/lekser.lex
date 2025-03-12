%option noyywrap
%option noinput
%option nounput

%{

#include <stdio.h>
#include <stdlib.h>

%}

%%

[abc]           { return *yytext; }

[ \t\n]         { }

.               {
    fprintf(stderr, "Leksicka greska: nepoznat karakter %c\n", *yytext);
    exit(EXIT_FAILURE);
}

%%
