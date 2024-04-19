#include <iostream>
#include <vector>

using namespace std;

void izmeni1(vector<int> v) {
    v.push_back(4);
}

void izmeni2(vector<int> *v) {
    v->push_back(4);
}

void izmeni3(vector<int> &v) {
    // referenca:
    //    - semantika pokazivaca
    //    - sintaksa obicne promenljive
    v.push_back(4);
}

ostream& operator<<(ostream &izlaz, const vector<int> &v) {
    for (int pom : v) {
        izlaz << pom << " ";
    }

    return izlaz;
}

int main() {
    vector<int> v; // implicitno se poziva odgovarajuci konstruktor vektora

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    izmeni1(v);
    cout << v << endl;

    izmeni2(&v);
    cout << v << endl;

    izmeni3(v);
    cout << v << endl;
}
