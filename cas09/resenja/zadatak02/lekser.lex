%option noyywrap
%option noinput
%option nounput

%{

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

// zasto na kraju ukljucujemo zaglavlje sa tokenima?
#include "parser.tab.hpp"

%}

%%

[0-9]+([.][0-9]+)?		{
	yylval.d = atof(yytext);
	return broj; 
}

[()+*\-/\n=]			{ return *yytext; }

[a-zA-Z_][a-zA-Z_0-9]*	{
	yylval.s = new string(yytext);
	return id;
}

#.*						{ }

[ \t]					{ }

.						{
	cerr << "Leksicka greska: " << yytext << endl;
	exit(EXIT_FAILURE);
}

%%
