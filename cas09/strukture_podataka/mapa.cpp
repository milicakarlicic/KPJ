#include <iostream>
#include <map>
#include <list>

using namespace std;

void ispisi(const map<string, double> &mapa) {
    for (pair<string, double> element : mapa) {
        cout << element.first << " : " << element.second << endl;
    }
}

int main() {
    map<string, double> mapa;

    mapa["marko"] = 9.5;
    mapa["ana"] = 10;
    mapa["milos"] = 7.3;
    mapa["milena"] = 8.5;
    mapa["mihajlo"] = 10;

    ispisi(mapa);

    mapa.erase("milos");

    cout << endl << "nakon brisanja: " << endl;
    ispisi(mapa);

    return 0;
}
