#include "Encryption.h"

Encryption::Encryption(int Rows, int Columns) {
    this->rows = Rows;
    this->columns = Columns;
}

void Encryption::print(const vector<vector<char>>& Str) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << Str[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<char>> Encryption::encr(const vector<vector<char>>& Str) {
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

vector<vector<char>> Encryption::decr(const vector<vector<char>>& Str) {
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
