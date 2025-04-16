#include <iostream>
#include <set>

using namespace std;

void ispisi(const set<string> &skup) {
    for (string pom : skup) {
        cout << pom << endl;
    }
}

int main() {
    set<string> skup;

    skup.insert("ana");
    skup.insert("marko");
    skup.insert("milos");
    skup.insert("milos");

    ispisi(skup);

    skup.erase("milos");

    cout << endl << "nakon brisanja: " << endl;
    ispisi(skup);

    return 0;
}
