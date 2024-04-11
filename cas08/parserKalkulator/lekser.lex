%option noyywrap
%option noinput
%option nounput

%{

#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"

%}

%%

[0-9]+			{ 
	yylval = atoi(yytext);
	return broj; 
}

[()+*]			{ return *yytext; }

[ \t\n]			{}

.				{
	fprintf(stderr, "Leksicka greska: %c\n", *yytext);
	exit(EXIT_FAILURE);
}

%%
