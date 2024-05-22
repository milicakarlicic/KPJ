%option noyywrap
%option noinput
%option nounput

%{

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "polinomi.hpp"

using namespace std;

#include "parser.tab.hpp"

%}

%%

-?[0-9]+([.][0-9]+)?    {
    yylval.d = atof(yytext);
    return broj;
}

[<>+\-*,()\n]           { return *yytext; }

"//".*                  { }

[ \t]                   { }

":="                    { return op_dodele; }

[a-zA-Z_][a-zA-Z_0-9]*  {
    // id
    yylval.s = new string(yytext);
    return id;
}

.                       {
    cerr << "Leksicka greska: " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%
