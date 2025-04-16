#include <iostream>
#include <list>

using namespace std;

void ispisi(const list<string> &lista) {
    for (string pom : lista) {
        cout << pom << endl;
    }
}

int main() {
    list<string> lista;

    lista.push_back("ana");
    lista.push_back("marko");
    lista.push_front("milos");
    lista.push_front("milos");

    ispisi(lista);

    lista.pop_back();

    cout << endl << "nakon brisanja: " << endl;
    ispisi(lista);

    return 0;
}
