%option noyywrap
%option nounput

%{
    #include <iostream>
    #include <vector>
    #include "funkcije.hpp"

    #include "parser.tab.hpp"
%}

%%

function                        { return function_token; }

sin                             { return sin_token; }

cos                             { return cos_token; }

[0-9]+([.][0-9]+)?              {
    yylval.d = atof(yytext);
    return broj;
}

[A-Z]                           {
    yylval.c = *yytext;
    return id_f;
}

[a-z]                           {
    yylval.c = *yytext;
    return id_p;
}

[+*(),="\n\[\]']                { return *yytext; }

[ \t]|"//".*                    {}

.                               {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%