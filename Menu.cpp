#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// Program 1: Encryption and Decryption with a class
void program1() {
    class MyClass {
    private:
        string str;
        int size;

    public:
        MyClass(const string& input, int n) {
            this->str = input;
            this->size = n;
        }

        void print(const string& str, int size) {
            cout << str;
            cout << endl;
        }

        string encryption(const string& text, const string& esh, const string& desh, int size) {
            string encr;
            for (int i = 0; i < size; i++) {
                char current = text[i];
                bool b = false;
                for (int j = 0; j < 26; j++) {
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

        string decryption(const string& text, const string& esh, const string& desh, int size) {
            string decr;
            for (int i = 0; i < size; i++) {
                char current = text[i];
                bool b = false;
                for (int j = 0; j < 26; j++) {
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

        char IsUnique(const string& desh, char newChar, int index) {
            while (true) {
                bool isUnique = true;
                for (int i = 0; i <= index; i++) {
                    if (newChar == desh[i]) {
                        isUnique = false;
                        break;
                    }
                }
                if (isUnique) {
                    return newChar;
                }
                newChar = rand() % 26 + 'a';
            }
        }
    };

    string esh, desh, text;
    cout << "Input text: ";
    getline(cin, text);
    MyClass myclass(text, text.length());

    esh.resize(26);
    for (int i = 0; i < 26; i++) {
        esh[i] = 'a' + i;
    }
    cout << endl << "Encryption alphabet: ";
    myclass.print(esh, esh.length());

    desh.resize(26);
    srand(time(0));
    for (int i = 0; i < 26; i++) {
        char newChar = rand() % 26 + 'a';
        desh[i] = myclass.IsUnique(desh, newChar, i);
    }
    cout << "Decryption alphabet: ";
    myclass.print(desh, desh.length());

    string en = myclass.encryption(text, esh, desh, text.length());
    cout << endl << "Encrypted text: ";
    myclass.print(en, en.length());
    cout << "Decrypted text: ";
    string dec = myclass.decryption(en, esh, desh, text.length());
    myclass.print(dec, dec.length());
}

// Program 2: Caesar Algorithm
void program2() {
    class MyClass {
    private:
        string str;
        int size;

    public:
        MyClass(const string& input, int n) {
            this->str = input;
            this->size = n;
        }

        void print(const string& str, int size) {
            cout << str;
            cout << endl;
        }

        string encryption(const string& text, const string& esh, const string& desh, int size) {
            string encr;
            for (int i = 0; i < size; i++) {
                char current = text[i];
                bool b = false;
                for (int j = 0; j < 26; j++) {
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

        string decryption(const string& text, const string& esh, const string& desh, int size) {
            string decr;
            for (int i = 0; i < size; i++) {
                char current = text[i];
                bool b = false;
                for (int j = 0; j < 26; j++) {
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

    string esh, desh, text;
    cout << "Input text: ";
    getline(cin, text);
    MyClass myclass(text, text.length());

    esh.resize(26);
    for (int i = 0; i < 26; i++) {
        esh[i] = 'a' + i;
    }
    cout << endl << "Encryption alphabet: ";
    myclass.print(esh, esh.length());

    desh.resize(26);
    for (int i = 0; i < 26; i++) {
        desh[i] = 'a' + i + 3;
    }
    desh[23] = 'a';
    desh[24] = 'b';
    desh[25] = 'c';
    cout << "Decryption alphabet: ";
    myclass.print(desh, desh.length());

    string en = myclass.encryption(text, esh, desh, text.length());
    cout << endl << "Encrypted text: ";
    myclass.print(en, en.length());
    cout << "Decrypted text: ";
    string dec = myclass.decryption(en, esh, desh, text.length());
    myclass.print(dec, dec.length());
}

// Program 3: Parz poxarinum
void program3() {
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
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    cout << str[i][j] << " ";
                }
                cout << endl;
            }
        }

        void encr(int size) {
            vector<vector<char>> newStr(columns, vector<char>(rows, ' '));
            for (int j = 0; j < columns; ++j) {
                for (int i = 0; i < rows; ++i) {
                    newStr[j][i] = str[i][j];
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

    int SIZE;
    string input;
    cout << "Enter size: ";
    cin >> SIZE;
    cin.ignore();
    cout << "Enter input string: ";
    getline(cin, input);
    int rows = (input.length() + SIZE - 1) / SIZE;
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
}

// Program 4: Run-Length Encoding
void program4() {
    class RLE {
    public:
        string encode(const string& input) {
            string encoded;
            int count = 1;

            for (int i = 1; i <= input.length(); i++) {
                if (i < input.length() && input[i] == input[i - 1]) {
                    count++;
                } else {
                    encoded += input[i - 1] + to_string(count);
                    count = 1;
                }
            }

            return encoded;
        }

        string decode(const string& encoded) {
            string decoded;
            for (int i = 0; i < encoded.length(); i++) {
                char currentChar = encoded[i];
                i++;
                string countStr;
                while (i < encoded.length() && isdigit(encoded[i])) {
                    countStr += encoded[i];
                    i++;
                }
                i--;

                int count = stoi(countStr);
                decoded.append(count, currentChar);
            }

            return decoded;
        }
    };

    RLE rle;
    string input = "aaabbbccd";
    string encoded = rle.encode(input);
    string decoded = rle.decode(encoded);

    cout << "Input: " << input << endl;
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;
}

int main() {
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Encryption and Decryption with Class\n";
        cout << "2. Caesar Algorithm\n";
        cout << "3. Parz poxarinum\n";
        cout << "4. Run-Length Encoding\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
            case 1:
                program1();
                break;
            case 2:
                program2();
                break;
            case 3:
                program3();
                break;
            case 4:
                program4();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
