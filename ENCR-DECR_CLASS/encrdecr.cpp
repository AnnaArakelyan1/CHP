#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

class MyClass {
private:
    string str;
    int size;

public:
    MyClass(const string& input, int n) : str(input), size(n) {}

    void print(const string& str) {
        cout << str << endl;
    }

    string encryption(const string& text, const vector<char>& esh, const vector<char>& desh) {
        string encr;
        for (int i = 0; i < text.size(); i++) {
            char current = text[i];
            bool found = false;
            for (int j = 0; j < 256; j++) {
                if (current == esh[j]) {
                    encr += desh[j];
                    found = true;
                    break;
                }
            }
            if (!found) {
                encr += current;
            }
        }
        return encr;
    }

    string decryption(const string& text, const vector<char>& esh, const vector<char>& desh) {
        string decr;
        for (int i = 0; i < text.size(); i++) {
            char current = text[i];
            bool found = false;
            for (int j = 0; j < 256; j++) {
                if (current == desh[j]) {
                    decr += esh[j];
                    found = true;
                    break;
                }
            }
            if (!found) {
                decr += current;
            }
        }
        return decr;
    }

    char generateUniqueChar(vector<char>& desh, int index) {
        while (true) {
            char newChar = rand() % 256;
            bool isUnique = true;
            for (int i = 0; i < index; i++) {
                if (newChar == desh[i]) {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique) {
                return newChar;
            }
        }
    }
};

int main() {
    vector<char> esh(256), desh(256);
    string text;

    cout << "Input text: ";
    getline(cin, text);
    MyClass myclass(text, text.length());
    for (int i = 0; i < 256; i++) {
        esh[i] = static_cast<char>(i);
    }
    cout << endl << "Encryption alphabet: ";
    myclass.print(string(esh.begin(), esh.end()));
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 256; i++) {
        desh[i] = myclass.generateUniqueChar(desh, i);
    }
    cout << "Decryption alphabet: ";
    myclass.print(string(desh.begin(), desh.end()));

    string encryptedText = myclass.encryption(text, esh, desh);
    cout << endl << "Encrypted text: ";
    myclass.print(encryptedText);

    cout << "Decrypted text: ";
    string decryptedText = myclass.decryption(encryptedText, esh, desh);
    myclass.print(decryptedText);

    return 0;
}
