//caesar algorithm
#include <iostream>
#include <string>
using namespace std;


class Caesar {
private:
    std::string str;
    int size;

public:


Caesar(const std::string& input, int n) {
    this->str = input;
    this->size = n;
}

void print(const std::string& str, int size) {
    std::cout << str;
    std::cout << std::endl;
}

std::string encryption(const std::string& text, const std::string& esh, const std::string& desh, int size) {
    std::string encr;
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

std::string decryption(const std::string& text, const std::string& esh, const std::string& desh, int size) {
    std::string decr;
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

};



// int main() {
//    string inputText;
//     cout << "Enter a string to encrypt: ";
//     getline(cin, inputText);

//     int shift;
//     cout << "Enter Caesar cipher shift value: ";
//     cin >> shift;
//     cin.ignore(); 

//     Caesar caesar(inputText, inputText.length());

//     string esh(256, ' '), desh(256, ' ');

//     for (int i = 0; i < 256; i++) {
//         esh[i] = static_cast<char>(i); 
//     }


//     for (int i = 0; i < 256; i++) {
//         desh[i] = static_cast<char>((i + shift) % 256);  
//     }

//     string en=caesar.encryption(text,esh,desh,text.length());
//     cout<<endl<<"Encrypted text: ";
//     caesar.print(en,en.length());
//     cout<<"Decrypted text: ";
//     string dec=caesar.decryption(en,esh,desh,text.length());
//     caesar.print(dec,dec.length());
//     return 0;
// }
