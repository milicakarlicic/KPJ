%option noyywrap
%option nounput
%option noinput

%{

#include <iostream>
#include <cstdlib>

#include "naredbe.hpp"

using namespace std;

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
    string pom = string(yytext);
    yylval.s = new string(pom.substr(1, pom.size() - 2));
    return string_token;
}

[0-9]+                  {
    yylval.b = atoi(yytext);
    return broj; }

0x[a-fA-F0-9]+          {
    // sscanf(yytext, "%x", &yylval.b)
    yylval.b = strtol(yytext, &yytext, 16);
    return broj;
}

[a-zA-Z_][a-zA-Z_0-9]*  {
    yylval.s = new string(yytext);
    return id;
}

[().;+:*<>]             { return *yytext; }

[ \t\n]                 {}

.                       {
    cerr << "Leksicka greska " << yytext << endl;
    exit(EXIT_FAILURE);
}

%%
