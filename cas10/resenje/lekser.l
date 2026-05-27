%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>

    #include "parser.tab.hpp"
%}


%%

[a-zA-Z_][a-zA-Z_0-9]*  {
    yylval.niska = new std::string(yytext);
    return id;
}

[0-9]+([.][0-9]+)?      { 
    yylval.realan_broj = atof(yytext); 
    return broj; 
}

[*\-/()\n+=]            { return *yytext; }

[ \t]                   { }

.                       {
    std::cerr << "Leksicka greska: "
    << yytext << std::endl;
}

%%