#include "Caesar.h"
#include <iostream>
using namespace std;

Caesar::Caesar(const string& input, int n) {
    this->str = input;
    this->size = n;
}

void Caesar::print(const string& str, int size) {
    cout << str;
    cout << endl;
}

string Caesar::encryption(const string& text, const string& esh, const string& desh, int size) {
    string encr;
    for (int i = 0; i < size; i++) {
        char current = text[i];
        bool b = false;
        for (int j = 0; j < 256; j++) {
            if (current == esh[j]) {
                encr += desh[j];
                b = true;
                break;
            }
        }
        if (!b) {
            encr += current;
        }
    }
    return encr;
}

string Caesar::decryption(const string& text, const string& esh, const string& desh, int size) {
    string decr;
    for (int i = 0; i < size; i++) {
        char current = text[i];
        bool b = false;
        for (int j = 0; j < 256; j++) {
            if (current == desh[j]) {
                decr += esh[j];
                b = true;
                break;
            }
        }
        if (!b) {
            decr += current;
        }
    }
    return decr;
}
