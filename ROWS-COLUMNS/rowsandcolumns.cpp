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

    void print(const std::vector<std::vector<char>>& Str) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                std::cout << Str[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<char>> encr(const std::vector<std::vector<char>>& Str) {
        std::vector<std::vector<char>> newStr(columns, std::vector<char>(rows, ' '));
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                newStr[j][i] = Str[i][j];
            }
        }

        std::cout << "Encrypted string:" << std::endl;
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                std::cout << newStr[j][i];
            }
        }
        std::cout << std::endl;
        return newStr;
    }

    std::vector<std::vector<char>> decr(const std::vector<std::vector<char>>& Str) {
        std::vector<std::vector<char>> original(rows, std::vector<char>(columns, ' '));
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                original[i][j] = Str[j][i];
            }
        }

        std::cout << "Decrypted string:" << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                std::cout << original[i][j];
            }
        }
        std::cout << std::endl;
        return original;
    }

};

//int main() {
//    int SIZE;
//    string input;
//    cout << "Enter size: ";
//    cin >> SIZE;
//    cin.ignore();
//    cout << "Enter input string: ";
//    getline(cin, input);
//
//    
//    int rows = (input.length() + SIZE - 1) / SIZE;
//    vector<vector<char>> str(rows, vector<char>(SIZE, ' '));
//
//   
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < SIZE; j++) {
//            int index = i * SIZE + j;
//            if (index < input.length()) {
//                str[i][j] = input[index];
//            }
//        }
//    }
//
//    Encryption encrypt(rows, SIZE);
//    encrypt.print(str); 
//    vector<vector<char>> encrypted = encrypt.encr(str);
//    encrypt.decr(encrypted);  
//
//    return 0;
//}
