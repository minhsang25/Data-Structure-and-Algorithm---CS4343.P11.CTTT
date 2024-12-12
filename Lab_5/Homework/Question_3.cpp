//STT: 25
//Full name: Le Minh Sang
//Homework

//Question 3. Implement Huffman coding using binary trees to compress text data. Create functions for
//building the Huffman tree and encoding/decoding messages.

#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// Node structure for the Huffman Tree
class HuffmanNode {
public:
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Compare function for priority queue
class Compare {
public:
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanCoding {
private:
    HuffmanNode* root;
    unordered_map<char, string> huffmanCodes;
    unordered_map<string, char> reverseCodes;

    // Recursive function to generate Huffman codes
    void generateCodes(HuffmanNode* node, string currentCode) {
        if (!node) return;

        // Leaf node
        if (!node->left && !node->right) {
            huffmanCodes[node->data] = currentCode;
            reverseCodes[currentCode] = node->data;
        }

        generateCodes(node->left, currentCode + "0");
        generateCodes(node->right, currentCode + "1");
    }

    // Clean up tree memory
    void cleanup(HuffmanNode* node) {
        if (!node) return;
        cleanup(node->left);
        cleanup(node->right);
        delete node;
    }

public:
    HuffmanCoding() : root(nullptr) {}

    ~HuffmanCoding() {
        cleanup(root);
    }

    // Build Huffman Tree
    void buildTree(const string& data) {
        // Calculate frequency of each character
        unordered_map<char, int> frequencyMap;
        for (char c : data) {
            frequencyMap[c]++;
        }

        // Create a priority queue to build the tree
        priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
        for (auto& pair : frequencyMap) {
            pq.push(new HuffmanNode(pair.first, pair.second));
        }

        // Build the tree
        while (pq.size() > 1) {
            HuffmanNode* left = pq.top(); pq.pop();
            HuffmanNode* right = pq.top(); pq.pop();

            HuffmanNode* combined = new HuffmanNode('\0', left->frequency + right->frequency);
            combined->left = left;
            combined->right = right;
            pq.push(combined);
        }

        // Root of the Huffman Tree
        root = pq.top();

        // Generate Huffman codes
        generateCodes(root, "");
    }

    // Encode a string
    string encode(const string& data) {
        string encodedString = "";
        for (char c : data) {
            encodedString += huffmanCodes[c];
        }
        return encodedString;
    }

    // Decode a string
    string decode(const string& encodedData) {
        string decodedString = "";
        string currentCode = "";

        for (char bit : encodedData) {
            currentCode += bit;
            if (reverseCodes.find(currentCode) != reverseCodes.end()) {
                decodedString += reverseCodes[currentCode];
                currentCode = "";
            }
        }

        return decodedString;
    }

    // Display Huffman codes
    void displayCodes() {
        for (auto& pair : huffmanCodes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
};

// Main function to demonstrate Huffman Coding
int main() {
    HuffmanCoding huffman;

    string data = "this is an example for huffman encoding";
    cout << "Original Data: " << data << endl;

    // Build Huffman Tree
    huffman.buildTree(data);

    // Display Huffman Codes
    cout << "\nHuffman Codes:\n";
    huffman.displayCodes();

    // Encode the data
    string encodedData = huffman.encode(data);
    cout << "\nEncoded Data: " << encodedData << endl;

    // Decode the data
    string decodedData = huffman.decode(encodedData);
    cout << "\nDecoded Data: " << decodedData << endl;

    return 0;
}
