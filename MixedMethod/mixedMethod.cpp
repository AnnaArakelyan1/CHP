#include <iostream>
#include <vector>
#include <string>
#include "caesar.cpp"  
#include "rowsandcols.cpp"
using namespace std;



int main() {
    string inputText;
    cout << "Enter a string to encrypt: ";
    getline(cin, inputText);

    int shift;
    cout << "Enter Caesar cipher shift value: ";
    cin >> shift;
    cin.ignore();

    Caesar caesar(inputText, inputText.length());

    string esh(256, ' '), desh(256, ' ');

    for (int i = 0; i < 256; i++) {
        esh[i] = static_cast<char>(i);
        /*esh += i;*/
    }


    for (int i = 0; i < 256; i++) {
        desh[i] = static_cast<char>((i + shift) % 256);
        /*desh += i;*/
    }

    string encryptedCaesar = caesar.encryption(inputText, esh, desh, inputText.length());
    cout << "Encrypted with Caesar cipher: " << encryptedCaesar << endl;


    int SIZE;
    cout << "Enter matrix size for transposition: ";
    cin >> SIZE;


    int rows = (encryptedCaesar.length() + SIZE - 1) / SIZE;
    vector<vector<char>> str(rows, vector<char>(SIZE, ' '));


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < SIZE; j++) {
            int index = i * SIZE + j;
            if (index < encryptedCaesar.length()) {
                str[i][j] = encryptedCaesar[index];
            }
        }
    }


    Encryption encrypt(rows, SIZE);
    vector<vector<char>> encryptedMatrix = encrypt.encr(str);
    cout << endl;


    vector<vector<char>> decryptedMatrix = encrypt.decr(encryptedMatrix);
    string decryptedText = "";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (decryptedMatrix[i][j] != ' ') {
                decryptedText += decryptedMatrix[i][j];
            }
        }
    }


    string finalDecrypted = caesar.decryption(decryptedText, esh, desh, decryptedText.length());
    cout << "Decrypted text (original): " << finalDecrypted << endl;

    return 0;
}

















