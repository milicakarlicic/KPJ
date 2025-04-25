%option noyywrap
%option noinput
%option nounput

%{
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "polinomi.hpp"

using namespace std;

#include "parser.tab.hpp"
%}

%%

":="							{ return dodjela; }

"=="							{ return jednako; }

"!=" 							{ return razlicito; }

-?[0-9]+([.][0-9]+)?			{
	yylval.d = atof(yytext);
	return broj;
}

[<>,+\-*\n()$'|\[\]]			{ return *yytext; }

[a-zA-Z_][a-zA-Z0-9_]*			{
	yylval.s = new string(yytext);
	return id;
}

[ \t]							{ }

. 								{
	cerr << "Leksicka greska " << yytext << endl;
	exit(EXIT_FAILURE);
}

%%
