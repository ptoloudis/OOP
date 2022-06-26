#include <iostream>
using namespace std;

bool t(){
    return 5 < 4;
}

int main(){
    cout << boolalpha;
    cout << t() << endl;
}