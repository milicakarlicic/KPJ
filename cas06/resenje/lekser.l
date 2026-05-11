%option noyywrap
%option nounput

%{
    #include <iostream>
    #include "tokeni.hpp"
%}

%%

"stampaj"                               { return stampaj; }

"sifra"                                 { return sifra; }

[a-zA-Z_][a-zA-Z_0-9]*                  { return id; }

[0-9]+\.[0-9]+                          { return broj; }

[0-9]+                                  { return broj; }

[+\-=;(),]                              { return *yytext; }

[ \t\n]                                 { }

.                                       {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%