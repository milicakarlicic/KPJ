%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include "tokeni.hpp"
%}

%%

0|[1-9][0-9]*               { return broj; }

[+*()]                      { return *yytext; }

[ \t\n]                     { }

.                           {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%