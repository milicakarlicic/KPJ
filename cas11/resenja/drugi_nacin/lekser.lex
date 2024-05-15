%option noyywrap
%option noinput
%option nounput

%{

#include <iostream>
#include <cstdlib>
#include <vector>
#include "polinomi.hpp"

using namespace std;

#include "parser.tab.hpp"

%}

%%

-?[0-9]+([.][0-9]+)?        {
    yylval.d = atof(yytext);
    return broj;
}

[+\-*<>,()\n]               { return *yytext; }

:=                          { return op_dodele; }

[a-zA-Z_][a-zA-Z_0-9]*      {
    yylval.s = new string(yytext);
    return id;
}

"//".*|[ \t]                { }

.                           {
    cerr << "Leksicka greska: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%
