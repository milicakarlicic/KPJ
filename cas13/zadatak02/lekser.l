%option noyywrap
%option nounput
%option noinput

%{

#include <iostream>
#include <cstdlib>
#include "naredbe.hpp"
#include "parser.tab.hpp"

%}

%%

"pocetak"               { return pocetak; }

"kraj"                  { return kraj; }

"ispisi"                { return ispisi; }

"mod"                   { return mod_token; }

"ako_je"                { return ako_je; }

"onda"                  { return onda; }

"inace"                 { return inace; }

"unesi"                 { return unesi; }

"dok_je"                { return dok_je; }

"radi_sledece"          { return radi_sledece; }

":="                    { return dodela; }

["]([^"]|\\["])*["]     {
    std::string pom(yytext);
    yylval.s = new std::string(pom.substr(1, pom.size() - 2));
    return string_token;
}

[0-9]+                  {
    yylval.broj = atoi(yytext);
    return broj; }

0[xX][a-fA-F0-9]+       {
    yylval.broj = strtol(yytext, NULL, 16);
    return broj;
}

[a-zA-Z_][a-zA-Z_0-9]*  {
    yylval.s = new std::string(yytext);
    return id;
}

[().;+:*<>]             { return *yytext; }

[ \t\n]                 {}

.                       {
    std::cerr << "Leksicka greska " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
