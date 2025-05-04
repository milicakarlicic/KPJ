%option noyywrap
%option nounput
%option noinput

%{

#include <iostream>
#include <cstdlib>
#include <vector>
#include "funkcije.hpp"

using namespace std;

#include "parser.tab.hpp"

%}

%%

function                { return function; }

sin                     { return sin_token; }

cos                     { return cos_token; }

[A-Z]                   {
    yylval.c = *yytext;
    return id_fje;
}

[a-z]                   {
    yylval.c = *yytext;
    return id;
}

[0-9]+([.][0-9]+)?      {
    yylval.d = atof(yytext);
    return broj;
}

[(),"+*=\n\[\]']        { return *yytext; }

[ \t]                   { }

.                       {
    cerr << "Leksicka greska: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%
