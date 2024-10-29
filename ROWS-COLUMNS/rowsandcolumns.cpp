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

    void print(vector<vector<char>> Str) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << Str[i][j] << " ";
            }
            cout << endl;
        }
    }
    void encr(vector<vector<char>> Str, int size){
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

    Encryption encrypt(rows, SIZE);
    encrypt.print(str);
    encrypt.encr(str,input.length());
    

    return 0;
}
