#include <iostream>
#include "tokeni.hpp"

#define YYDEBUG

extern int yylex();

int preduvid;

void greska(std::string poruka) {
    std::cerr << "Sintaksna greska: " << poruka << std::endl;
    exit(EXIT_FAILURE);
}

/*
----------------------------------------------------------------------
Naivna gramatika:

    NIZ_NAREDBI ->  NAREDBA ; NIZ_NAREDBI
                 | NAREDBA ;
    NAREDBA ->  int_token id = E
              | print_token ( E )
    E ->  E '|' T
        | T
    T ->  T & F
        | F
    F ->  ~F
        | broj
        | id
----------------------------------------------------------------------
Transformisana gramatika sa skupovima izbora:

    NIZ_NAREDBI ->  NAREDBA ; NIZ_NAREDBI'    {int_token, print_token}
    NIZ_NAREDBI' ->  NIZ_NAREDBI              {int_token, print_token}
    NIZ_NAREDBI' -> eps                       {eoi}
    NAREDBA ->  int_token id = E              {int_token}
              | print_token ( E )             {print_token}
    E ->  T E'                                {~, broj, id}
    E' ->  '|' T E'                           {|}
          | eps                               {;, )}
    T ->  F T'                                {~, broj, id)}
    T' ->  & F T'                             {&}
         | eps                                {;, ), |}
    F ->  ~ F                                 {~}
        | broj                                {broj}
        | id                                  {id}
----------------------------------------------------------------------
*/

void NIZ_NAREDBI();
void NIZ_NAREDBI_P();
void NAREDBA();
void E();
void EP();
void T();
void TP();
void F();

int main() {
    preduvid = yylex();

    NIZ_NAREDBI();

    if (preduvid == eoi) {
        std::cout << "Recenica pripada gramatici" << std::endl;
    } else {
        std::cout << "Recenica NE pripada gramatici" << std::endl;
    }
}

void NIZ_NAREDBI() {
    if (preduvid == int_token || preduvid == print_token) {
#ifdef YYDEBUG
        std::cout << "NIZ_NAREDBI -> NAREDBA NIZ_NAREDBI'\n";
#endif
        NAREDBA();
        NIZ_NAREDBI_P();
    } else {
        greska("[NIZ_NAREDBI] Ocekivani tokeni int_token ili print_token");
    }
}

void NIZ_NAREDBI_P() {
    if (preduvid == int_token || preduvid == print_token) {
#ifdef YYDEBUG
        std::cout << "NIZ_NAREDBI' -> NIZ_NAREDBI\n";
#endif
        NIZ_NAREDBI();
    } else if (preduvid == eoi) {
#ifdef YYDEBUG
        std::cout << "NIZ_NAREDBI' -> eps\n";
#endif
    } else {
        greska("[NIZ_NAREDBI'] Ocekivani tokeni int_token, print_token ili eoi");
    }
}

void NAREDBA() {
    if (preduvid == int_token) {
#ifdef YYDEBUG
        std::cout << "NAREDBA -> int_token id = E ;\n";
#endif
        preduvid = yylex();

        if (preduvid != id)
            greska("[NAREDBA] Ocekivani tokeni id");
        preduvid = yylex();

        if (preduvid != '=')
            greska("[NAREDBA] Ocekivani tokeni =");
        preduvid = yylex();

        E();

        if (preduvid != ';')
            greska("[NAREDBA] Ocekivani tokeni ;");
        preduvid = yylex();

    } else if (preduvid == print_token) {
#ifdef YYDEBUG
        std::cout << "NAREDBA -> print_token ( E ) ;\n";
#endif
        preduvid = yylex();

        if (preduvid != '(')
            greska("[NAREDBA] Ocekivani tokeni (");
        preduvid = yylex();

        E();

        if (preduvid != ')')
            greska("[NAREDBA] Ocekivani tokeni )");
        preduvid = yylex();

        if (preduvid != ';')
            greska("[NAREDBA] Ocekivani tokeni ;");
        preduvid = yylex();

    } else {
        greska("[NAREDBA] Ocekivani tokeni int_token ili print_token");
    }
}

void E() {
    if (preduvid == '~' || preduvid == broj || preduvid == id) {
#ifdef YYDEBUG
        std::cout << "E -> T E'\n";
#endif
        T();
        EP();
    } else {
        greska("[E] Ocekivani tokeni ~, broj ili id");
    }
}

void EP() {
    if (preduvid == '|') {
#ifdef YYDEBUG
        std::cout << "E' -> | T E'\n";
#endif
        preduvid = yylex();
        T();
        EP();
    } else if (preduvid == ';' || preduvid == ')') {
#ifdef YYDEBUG
        std::cout << "E' -> eps\n";
#endif
    } else {
        greska("[E'] Ocekivani tokeni |, ; ili )");
    }
}

void T() {
    if (preduvid == '~' || preduvid == broj || preduvid == id) {
#ifdef YYDEBUG
        std::cout << "T -> F T'\n";
#endif
        F();
        TP();
    } else {
        greska("[T] Ocekivani tokeni ~, broj ili id");
    }
}

void TP() {
    if (preduvid == '&') {
#ifdef YYDEBUG
        std::cout << "T' -> & F T'\n";
#endif
        preduvid = yylex();
        F();
        TP();
    } else if (preduvid == '|' || preduvid == ';' || preduvid == ')') {
#ifdef YYDEBUG
        std::cout << "T' -> eps\n";
#endif
    } else {
        greska("[T'] Ocekivani tokeni &, |, ; ili )");
    }
}

void F() {
    if (preduvid == '~') {
#ifdef YYDEBUG
        std::cout << "F -> ~ F\n";
#endif
        preduvid = yylex();
        F();
    } else if (preduvid == broj) {
#ifdef YYDEBUG
        std::cout << "F -> broj\n";
#endif
        preduvid = yylex();
    } else if (preduvid == id) {
#ifdef YYDEBUG
        std::cout << "F -> id\n";
#endif
        preduvid = yylex();
    } else {
        greska("[F] Ocekivani tokeni ~, broj ili id");
    }
}