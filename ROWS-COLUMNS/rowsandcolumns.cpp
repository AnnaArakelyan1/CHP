#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Encryption {
private:
    vector<vector<char>> str;
    int rows;
    int columns;

public:
    Encryption(vector<vector<char>> Str, int Rows, int Columns) {
        this->str = Str;
        this->rows = Rows;
        this->columns = Columns;
    }

    void print() {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                cout << str[i][j] << " ";
            }
            cout << endl;
        }
    }
    void encr(int size){
        vector<vector<char>> newStr(columns, vector<char>(rows, ' '));
        for (size_t j = 0; j < columns; ++j) {
            for (size_t i = 0; i < rows; ++i) {
                newStr[j][i] = str[i][j];
            }
        }

        cout << "Encrypted string:" << endl;
        for (size_t j = 0; j < columns; ++j) {
            for (size_t i = 0; i < rows; ++i) {
                cout << newStr[j][i];
            }
        }
        
    }
};

int main() {
    int SIZE;
    string input;
    cout << "Enter size: ";
    cin >> SIZE;
    cin.ignore();
    cout << "Enter input string: ";
    getline(cin,input);
    int rows = (input.length()+SIZE-1) / SIZE;
    vector<vector<char>> str(rows, vector<char>(SIZE, ' '));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < SIZE; j++) {
            int index = i * SIZE + j;
            if (index < input.length()) {
                str[i][j] = input[index];
            }
        }
    }

    Encryption encrypt(str, rows, SIZE);
    encrypt.print();
    encrypt.encr(input.length());
    

    return 0;
}
