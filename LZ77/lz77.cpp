#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

std::string compress(const std::string &input, int searchBufferSize, int maxLength) {
    std::stringstream compressedStream;
    int i = 0;
    int n = input.size();

    while (i < n) {
        int maxLengthFound = 0;
        int bestOffset = 0;
        char nextChar = input[i];
        
        int searchStart = std::max(0, i - searchBufferSize);

        for (int j = searchStart; j < i; ++j) {
            int length = 0;
            while (i + length < n && length < maxLength && input[j + length] == input[i + length]) {
                ++length;
            }

            if (length > maxLengthFound) {
                maxLengthFound = length;
                bestOffset = i - j;
                nextChar = (i + length < n) ? input[i + length] : '\0';
            }
        }

        if (maxLengthFound > 1) {
            compressedStream << "[" << bestOffset << "|" << maxLengthFound << "]";
            i += maxLengthFound; 
        } else {
            compressedStream << input[i]; 
            ++i;
        }
    }

    return compressedStream.str();
}

int main() {
    std::string input = "hahahahaha"; 
    int searchBufferSize = 6;  
    int maxLength = 6;        

    std::string compressedOutput = compress(input, searchBufferSize, maxLength);

    std::cout << "Compressed output: " << compressedOutput << "\n";
    return 0;
}
