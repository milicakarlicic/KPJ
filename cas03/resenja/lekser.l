%option noyywrap
%option noinput
%option nounput

%{
    #include <iostream>
%}

%%

[abc]               { return *yytext; } 

[ \t\n]             { }

.                   {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
