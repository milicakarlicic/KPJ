#include <iostream>
#include <set>

std::ostream& operator<<(std::ostream& izlaz, const std::set<std::string>& skup) {
    for (const auto& element : skup) {
        izlaz << element << std::endl;
    }
    return izlaz;
}

int main() {
    std::set<std::string> skup;

    skup.insert("ana");
    skup.insert("marko");
    skup.insert("milos");
    skup.insert("milos");

    std::cout << "pre brisanja: " << std::endl;
    std::cout << skup;

    skup.erase("milos");

    std::cout << std::endl << "nakon brisanja: " << std::endl;
    std::cout << skup;

    return 0;
}
