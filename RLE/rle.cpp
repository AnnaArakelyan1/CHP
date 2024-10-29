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
            } else {
                encoded += input[i - 1];

             
                char asciiCount[30];
                int len = 0;

                while (count > 0) {
                    asciiCount[len++] = (count % 10) + '0';
                    count /= 10;
                }

          
                for (int k = 0; k < len / 2; k++) {
                    swap(asciiCount[k], asciiCount[len - 1 - k]);
                }

           
                asciiCount[len] = '\0';
                encoded += asciiCount; 
                count = 1; 
            }
        }

        return encoded;
    }
    
    
    
    string decode(const string& encoded) {
    string decoded;

    for (size_t i = 0; i < encoded.length();) { 
        char currentChar = encoded[i]; 
        i++; 

        string countStr;


        while (i < encoded.length() && isdigit(encoded[i])) {
            countStr += encoded[i];
            i++; 
        }

        int count = 0;
        for (char digit : countStr) {
            count = count * 10 + (digit - '0'); 
        }

        decoded.append(count, currentChar);  
    }

    return decoded;
}


    
};

int main() {
    RLE rle;
    string input = "abbbccd";
    string encoded = rle.encode(input);
    string decoded = rle.decode(encoded);

    cout << "Input: " << input << endl;
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}
