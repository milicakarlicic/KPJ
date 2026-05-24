%option noyywrap
%option nounput

%{
    #include <iostream>
    #include "parser.tab.hpp"
%}

%%

[0-9]+([.][0-9]+)?              { return broj; }

[*+/\-()\n]                     { return *yytext; }

[ \t]                           {}

.                               {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
