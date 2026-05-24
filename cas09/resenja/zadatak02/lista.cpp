#include <iostream>
#include <list>

std::ostream& operator<<(std::ostream& izlaz, const std::list<std::string>& lista) {
    for (const auto& element : lista) {
        izlaz << element << std::endl;
    }
    return izlaz;
}

int main() {
    std::list<std::string> lista;

    lista.push_back("ana");
    lista.push_back("marko");
    lista.push_front("milos");
    lista.push_front("milos");

    std::cout << "pre brisanja: " << std::endl;
    std::cout << lista;

    lista.pop_back();

    std::cout << std::endl << "nakon brisanja: " << std::endl;
    std::cout << lista;

    return 0;
}
