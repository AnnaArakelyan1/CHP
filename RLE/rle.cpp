#include <iostream>
#include <string>
#include <vector>
using namespace std;


class RLE {
    
public:
 
string encode(const string& input) {
        string encoded;
        int count = 1;

        for (int i = 1; i <= input.length(); i++) {
            if (i < input.length() && input[i] == input[i - 1]) {
                count++;
            }
            else {
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

            int count =stoi(countStr);
            decoded.append(count, currentChar);
        }

        return decoded;
    }
    
    
};

int main() {
    RLE rle;
    string input = "aaabbbccd";
    string encoded = rle.encode(input);
    string decoded = rle.decode(encoded);

    cout << "Input: " << input << endl;
    cout << "Encoded: " << encoded <<endl;
    cout << "Decoded: " << decoded <<endl;

    return 0;
}
