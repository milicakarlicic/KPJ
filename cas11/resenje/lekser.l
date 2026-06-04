%option noyywrap
%option nounput

%{
    #include <iostream>
    #include <vector>
    #include "polinomi.hpp"

    #include "parser.tab.hpp"
%}

%%

[a-zA-Z_][a-zA-Z_0-9]*          {
    yylval.s = new std::string(yytext);
    return id;
}

:=                              { return dodela; }

-?[0-9]+([.][0-9]+)?            { 
    yylval.d = atof(yytext);
    return broj; 
}   

[,<>\n+\-*()]                   { return *yytext; }

[ \t]                           { }

.                               {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%