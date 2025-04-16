#include <iostream>
#include <vector>

using namespace std;

void ispisi(const vector<string> &niz) {
    for (string pom : niz) {
        cout << pom << endl;
    }
}

int main() {
    vector<string> niz;

    niz.push_back("ana");
    niz.push_back("marko");
    niz.push_back("milos");
    niz.push_back("milos");

    ispisi(niz);

    niz.pop_back();

    cout << endl << "nakon brisanja: " << endl;
    ispisi(niz);

    return 0;
}
