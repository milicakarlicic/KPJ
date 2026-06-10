%option noyywrap
%option nounput

%{
    #include <iostream>
    #include "funkcije.hpp"

    #include "parser.tab.hpp"
%}

%%

function                        { return function_token; }

sin                             { return sin_token; }

cos                             { return cos_token; }

[0-9]+([.][0-9]+)?              {
    return broj;
}

[A-Z]                           {
    return id_f;
}

[a-z]                           {
    return id_p;
}

[+*(),="\n]                     { return *yytext; }

[ \t]                           {}

.                               {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%