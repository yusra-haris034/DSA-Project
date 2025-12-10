#include "rollingHash.h"
#include <iostream>

using namespace std;

int main() {
    RollingHash rh;

    string dna = "ACGTAC";
    int window = 3;

    cout << "DNA string: " << dna << endl;
    cout << "Window size: " << window << endl << endl;

    string firstWindow = dna.substr(0, window);

    long long h = rh.computeHash(firstWindow);
    cout << "Initial window: " << firstWindow << endl;
    cout << "Initial hash:   " << h << endl << endl;

    for (int i = 1; i <= dna.length() - window; i++) {
        char oldChar = dna[i - 1];
        char newChar = dna[i + window - 1];

        h = rh.rollHash(h, oldChar, newChar, window);

        string current = dna.substr(i, window);

        cout << "Window: " << current 
             << " | Hash: " << h << endl;
    }

    cout << endl << "Testing power():" << endl;
    cout << "BASE^5 % MOD = " << rh.power(5) << endl;

    return 0;
}
