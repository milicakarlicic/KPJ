#include <iostream>
#include <map>

std::ostream& operator<<(std::ostream& izlaz, const std::map<std::string, double>& m) {
    for (const auto& element : m) {
        izlaz << element.first << " : " << element.second << std::endl;
    }
    return izlaz;
}

int main() {
    std::map<std::string, double> mapa;

    mapa["marko"] = 9.5;
    mapa["ana"] = 10;
    mapa["milos"] = 7.3;
    mapa["milena"] = 8.5;

    std::cout << "pre brisanja: " << std::endl;
    std::cout << mapa;

    mapa.erase("milos");

    std::cout << std::endl << "nakon brisanja: " << std::endl;
    std::cout << mapa;

    return 0;
}
