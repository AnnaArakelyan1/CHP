#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Encryption {
private:
    int rows;
    int columns;

public:
    Encryption(int Rows, int Columns) {
        this->rows = Rows;
        this->columns = Columns;
    }

    void print(const vector<vector<char>>& Str) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << Str[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<vector<char>> encr(const vector<vector<char>>& Str) {
        vector<vector<char>> newStr(columns, vector<char>(rows, ' '));
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                newStr[j][i] = Str[i][j];
            }
        }

        cout << "Encrypted string:" << endl;
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                cout << newStr[j][i];
            }
        }
        cout << endl;
        return newStr;
    }

    vector<vector<char>> decr(const vector<vector<char>>& Str) {
        vector<vector<char>> original(rows, vector<char>(columns, ' '));
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                original[i][j] = Str[j][i];
            }
        }

        cout << "Decrypted string:" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << original[i][j];
            }
        }
        cout << endl;
        return original;
    }
};

// int main() {
//     int SIZE;
//     string input;
//     cout << "Enter size: ";
//     cin >> SIZE;
//     cin.ignore();
//     cout << "Enter input string: ";
//     getline(cin, input);
    
//     int rows = (input.length() + SIZE - 1) / SIZE;
//     vector<vector<char>> str(rows, vector<char>(SIZE, ' '));

//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < SIZE; j++) {
//             int index = i * SIZE + j;
//             if (index < input.length()) {
//                 str[i][j] = input[index];
//             }
//         }
//     }

//     Encryption encrypt(rows, SIZE);
//     encrypt.print(str);
//     vector<vector<char>> encrypted = encrypt.encr(str);
//     encrypt.decr(encrypted);

//     return 0;
// }
