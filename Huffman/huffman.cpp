#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
using namespace std;

struct Node {
    char ch;    
    int freq;             
    Node* left;        
    Node* right;        

    // Constructor for internal nodes
    Node(int frequency, Node* leftChild = nullptr, Node* rightChild = nullptr)
        : ch('\0'), freq(frequency), left(leftChild), right(rightChild) {}

    // Constructor for leaf nodes
    Node(char character, int frequency)
        : ch(character), freq(frequency), left(nullptr), right(nullptr) {}

    // Compare nodes for priority queue (min-heap)
    bool operator>(const Node& other) const {
        return freq > other.freq;
    }
};

// Generate the Huffman codes from the tree
void generateCodes(Node* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) return;

    // If it's a leaf node, save the code
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->ch] = code;
    }

    // Traverse the left and right subtree
    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Build the Huffman tree
Node* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, greater<Node*>> minHeap;

    // Create a node for each character and insert it into the priority queue
    for (const auto& pair : frequencies) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Combine two nodes with the smallest frequencies until we have only one node (the root)
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with the sum of the frequencies
        Node* internalNode = new Node(left->freq + right->freq, left, right);
        minHeap.push(internalNode);
    }

    // The remaining node is the root of the Huffman tree
    return minHeap.top();
}

// Encode a string using the Huffman codes
string encode(const string& text, const unordered_map<char, string>& huffmanCodes) {
    string encodedString;
    for (char ch : text) {
        encodedString += huffmanCodes.at(ch);
    }
    return encodedString;
}

// Decode a string using the Huffman tree
string decode(const string& encodedText, Node* root) {
    string decodedString;
    Node* currentNode = root;

    for (char bit : encodedText) {
        // Traverse the tree based on the bit
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {
            currentNode = currentNode->right;
        }

        // If it's a leaf node, append the character to the result
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            decodedString += currentNode->ch;
            currentNode = root;  // Start from the root again
        }
    }

    return decodedString;
}

int main() {
    string text = "abbcccdddd";

    // Step 1: Calculate frequencies of characters in the input text
    unordered_map<char, int> frequencies;
    for (char ch : text) {
        frequencies[ch]++;
    }

    // Step 2: Build the Huffman tree
    Node* root = buildHuffmanTree(frequencies);

    // Step 3: Generate the Huffman codes
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    // Step 4: Display the Huffman codes
    cout << "Huffman Codes:" << endl;
    for (const auto& pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Step 5: Encode the input text
    string encodedText = encode(text, huffmanCodes);
    cout << "\nEncoded Text: " << encodedText << endl;

    // Step 6: Decode the encoded text back to the original
    string decodedText = decode(encodedText, root);
    cout << "\nDecoded Text: " << decodedText << endl;

    return 0;
}
