#include <iostream>
#include <vector>

void izmeni1(std::vector<int> v) {
    v.push_back(4);
}

void izmeni2(std::vector<int>* v) {
    v->push_back(4);
}

void izmeni3(std::vector<int>& v) {
    v.push_back(4);
}

std::ostream& operator<<(std::ostream& izlaz, const std::vector<int>& v) {
    for (int pom : v) {
        izlaz << pom << " ";
    }

    return izlaz;
}

int main() {
    std::vector<int> v; 
    
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    std::cout << v << std::endl;
    izmeni3(v);
    std::cout << v << std::endl;
}