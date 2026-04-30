#include <iostream>
#include <stack>
#include "tokeni.hpp"

#define YYDEBUG

extern int yylex();

void greska(std::string poruka) {
    std::cerr << "Sintaksna greska: " << poruka << std::endl;
    exit(EXIT_FAILURE);
}

int main() {
    int preduvid;
    std::stack<int> stek;
    stek.push(NIZ_NAREDBI);

    preduvid = yylex();

    while (!stek.empty()) {
        int element = stek.top();
        stek.pop();
        switch(element) {
            case NIZ_NAREDBI:
                if (preduvid == sifra || preduvid == stampaj) {
#ifdef YYDEBUG
                    std::cout << "NIZ_NAREDBI -> NAREDBA ; NIZ_NAREDBI'\n";
#endif
                    stek.push(NIZ_NAREDBIP);
                    stek.push(';');
                    stek.push(NAREDBA);
                } else {
                    greska("[NIZ_NAREDBI] Ocekivani tokeni sifra ili stampaj");
                }
                break;
            case NIZ_NAREDBIP:
                if (preduvid == stampaj || preduvid == sifra) {
#ifdef YYDEBUG
                    std::cout << "NIZ_NAREDBI' -> NAREDBA ; NIZ_NAREDBI'\n";
#endif
                    stek.push(NIZ_NAREDBIP);
                    stek.push(';');
                    stek.push(NAREDBA);
                } else if (preduvid == eoi) {
#ifdef YYDEBUG
                    std::cout << "NIZ_NAREDBI' -> Eps\n";
#endif
                } else {
                    greska("[NIZ_NAREDBIP] Ocekivani tokeni sifra ili stampaj ili eoi");
                }
                break;
            case NAREDBA:
                if (preduvid == sifra) {
#ifdef YYDEBUG
                    std::cout << "NAREDBA -> sifra id NAREDBA'\n";
#endif
                    stek.push(NAREDBAP);
                    stek.push(id);
                    stek.push(sifra);
                } else if (preduvid == stampaj) {
#ifdef YYDEBUG
                    std::cout << "NAREDBA -> stampaj E\n";
#endif
                    stek.push(E);
                    stek.push(stampaj);
                } else {
                    greska("[NAREDBA] Ocekivani tokeni sifra ili stampaj");
                }
                break;
            case NAREDBAP: 
                if (preduvid == ';') {
#ifdef YYDEBUG
                    std::cout << "NAREDBA' -> Eps\n";
#endif
                } else if (preduvid == '(') {
#ifdef YYDEBUG                    
                    std::cout << "NAREDBA' -> ( broj , broj )\n"; 
#endif
                    stek.push(')');
                    stek.push(broj);
                    stek.push(',');
                    stek.push(broj);
                    stek.push('(');
                } else if (preduvid == '=') {
#ifdef YYDEBUG
                    std::cout << "NAREDBA' -> = E\n";
#endif
                    stek.push(E);
                    stek.push('=');
                } else {
                    greska("[NAREDBA'] Ocekivani tokeni ;, ( ili =");
                }
                break;
            case E:
                if (preduvid == broj || preduvid == id) {
#ifdef YYDEBUG                    
                    std::cout << "E -> T E'\n";
#endif  
                    stek.push(EP);
                    stek.push(T);
                } else {
                    greska("[E] Ocekivani tokeni broj ili id");
                }
                break;
            case EP:
                if (preduvid == '+') {
#ifdef YYDEBUG                    
                    std::cout << "E' -> + T E'\n";
#endif
                    stek.push(EP);
                    stek.push(T);
                    stek.push('+');
                } else if (preduvid == '-') {
#ifdef YYDEBUG                    
                    std::cout << "E' -> - T E'\n";
#endif
                    stek.push(EP);
                    stek.push(T);
                    stek.push('-');
                } else if (preduvid == ';') {
#ifdef YYDEBUG                    
                    std::cout << "E' -> Eps\n";
#endif
                } else {
                    greska("[E'] Ocekivani tokeni +, - ili ;");
                }
                break;
            case T:
                if (preduvid == broj) {
#ifdef YYDEBUG                    
                    std::cout << "T -> broj\n";
#endif
                    stek.push(broj);
                } else if (preduvid == id) {
#ifdef YYDEBUG                    
                    std::cout << "T -> id\n";
#endif
                    stek.push(id);
                } else {
                    greska("[T] Ocekivani tokeni broj ili id");
                }
                break;
            default:
                if (element != preduvid) {
                    greska("Nepoklapanje tokena");
                }
                preduvid = yylex();
                break;
        }
    }

    if (preduvid == eoi) {
        std::cout << "Recenica pripada gramatici\n";
    } else {
        std::cout << "Recenica ne pripada gramatici\n";
    }

    return 0;
}