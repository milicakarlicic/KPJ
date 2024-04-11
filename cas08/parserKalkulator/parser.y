
%{

// kalkulator - prva verzija

#include <stdio.h>
#include <stdlib.h>

#define YYDEBUG 1

extern int yylex();

void yyerror(char* poruka) {
	fprintf(stderr, "%s\n", poruka);
	exit(EXIT_FAILURE);
}

%}

// direktiva kojom definisemo da je broj token
%token broj

// asocijativnost + prioritet
%left '+'
%left '*'

%%

S: E {
	// podrazumijevana akcija $$ = $1
	printf("%d\n", $$);
}
;
E: E '+' E {
	// $$ - vrijednost atributa neterminala sa lijeve strane pravila tj. neterminala E
	// $1 - vrijednost atributa prvog E sa desne strane pravila
	// $2 - vrijednost atributa '+'
	// $3 - vrijednost atributa drugog E sa desne strane pravila
	$$ = $1 + $3;
}
| E '*' E {
	$$ = $1 * $3;
}
| '(' E ')' {
	$$ = $2;
}
| broj {
	$$ = $1;
}
;

%%

int main() {
	//yydebug = 1;
	yyparse();
}
