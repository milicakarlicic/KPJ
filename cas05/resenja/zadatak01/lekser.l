%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
    #include "tokeni.hpp"
%}


%%

"int"                               { return int_token; }

"print"                             { return print_token; }

[a-zA-Z_][a-zA-Z_0-9]*              { return id; }

0|[1-9][0-9]*                       { return broj; }

0(0|[1-7][0-7]*)                    { return broj; }

0[xX](0|[1-9a-fA-F][0-9a-fA-F]*)    { return broj; }

[=;&|~()]                           { return *yytext; }

[ \t\n]                             { }

.                                   {
    std::cout << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%