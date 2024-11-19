#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct LZ77Triplet {
    int offset;
    int length;
    char next_char;
};


std::vector<LZ77Triplet> lz77_compress(const std::string& input, int window_size) {
    std::vector<LZ77Triplet> result;
    int input_size = input.size();

    for (int i = 0; i < input_size;) {
        int match_offset = 0, match_length = 0;
        char next_char = input[i];

        int start = std::max(0, i - window_size);

        for (int j = start; j < i; ++j) {
            int length = 0;

            while (i + length < input_size && input[j + length] == input[i + length]) {
                ++length;
            }

       
            if (length > match_length) {
                match_length = length;
                match_offset = i - j;
            }
        }

        if (match_length > 2) {
            next_char = (i + match_length < input_size) ? input[i + match_length] : '\0';
            result.push_back({ match_offset, match_length, next_char });
            i += match_length + 1; 
        } else {
          
            result.push_back({ 0, 0, input[i] });
            ++i; 
        }
    }

    return result;
}

// Function to display the compressed output
void display_compression(const std::vector<LZ77Triplet>& triplets) {
    std::ostringstream output;
    for (const auto& triplet : triplets) {
        if (triplet.offset == 0 && triplet.length == 0) {
            output << triplet.next_char;
        } else {
            output << "[" << triplet.offset << "|" << triplet.length << "]";
            if (triplet.next_char != '\0') {
                output << triplet.next_char;
            }
        }
    }
    std::cout << "Compressed output: " << output.str() << std::endl;
}


int main() {
    std::string input = "The compression and the decompression leave an impression. Hahaha!";
    int window_size = 32; 

    auto compressed = lz77_compress(input, window_size);
    display_compression(compressed);

    return 0;
}
