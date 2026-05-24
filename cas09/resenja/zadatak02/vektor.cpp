#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& izlaz, const std::vector<std::string>& niz) {
    for (const auto& element : niz) {
        izlaz << element << std::endl;
    }
    return izlaz;
}

int main() {
    std::vector<std::string> niz;

    niz.push_back("ana");
    niz.push_back("marko");
    niz.push_back("milos");
    niz.push_back("milos");

    std::cout << "pre brisanja: " << std::endl;
    std::cout << niz;

    niz.pop_back();

    std::cout << std::endl << "nakon brisanja: " << std::endl;
    std::cout << niz;

    return 0;
}
