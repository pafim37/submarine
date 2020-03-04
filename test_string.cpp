#include <string>
#include <iostream>
using namespace std;

class B {
    public: 
    string t;
    B(string);
};

B::B(string t) {
    this->t = t;
}

int main() {
    B b("HELLLLLOOOOOO");
    cout << (b.t).length() << endl;
}