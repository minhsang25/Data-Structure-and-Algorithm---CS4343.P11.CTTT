//STT: 25
//Full name: Le Minh Sang
//Homework

//Question 6. Build a Merkle tree to verify the integrity of data blocks in a distributed system. Implement
// functions to generate hashes and verify data authenticity using the root hash.
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h> // To use SHA-256 hashing

using namespace std;

// Utility function to calculate SHA-256 hash
string sha256(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Merkle Tree Node
class MerkleNode {
public:
    string hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(const string& hash) : hash(hash), left(nullptr), right(nullptr) {}
};

// Merkle Tree Class
class MerkleTree {
private:
    MerkleNode* root;

    // Build the Merkle Tree from a list of hashes
    MerkleNode* buildTree(vector<string>& hashes) {
        if (hashes.empty()) return nullptr;

        vector<MerkleNode*> nodes;
        for (const string& h : hashes) {
            nodes.push_back(new MerkleNode(h));
        }

        while (nodes.size() > 1) {
            vector<MerkleNode*> newLevel;
            for (size_t i = 0; i < nodes.size(); i += 2) {
                if (i + 1 < nodes.size()) {
                    string combinedHash = sha256(nodes[i]->hash + nodes[i + 1]->hash);
                    MerkleNode* parent = new MerkleNode(combinedHash);
                    parent->left = nodes[i];
                    parent->right = nodes[i + 1];
                    newLevel.push_back(parent);
                } else {
                    // If odd number of nodes, carry the last one up
                    newLevel.push_back(nodes[i]);
                }
            }
            nodes = newLevel;
        }

        return nodes[0]; // The root node
    }

    // Recursively delete nodes to free memory
    void deleteTree(MerkleNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    MerkleTree() : root(nullptr) {}

    ~MerkleTree() {
        deleteTree(root);
    }

    // Build the Merkle Tree from a list of data blocks
    void build(const vector<string>& dataBlocks) {
        vector<string> hashes;
        for (const string& data : dataBlocks) {
            hashes.push_back(sha256(data));
        }
        root = buildTree(hashes);
    }

    // Get the root hash of the Merkle Tree
    string getRootHash() {
        return root ? root->hash : "";
    }

    // Verify if a data block is part of the tree
    bool verifyData(const string& data, const vector<string>& proof, const string& rootHash) {
        string currentHash = sha256(data);

        for (const string& siblingHash : proof) {
            currentHash = sha256(currentHash + siblingHash);
        }

        return currentHash == rootHash;
    }

    // Generate the proof for a data block
    vector<string> generateProof(const string& data, const vector<string>& dataBlocks) {
        vector<string> hashes;
        for (const string& d : dataBlocks) {
            hashes.push_back(sha256(d));
        }

        vector<MerkleNode*> nodes;
        for (const string& h : hashes) {
            nodes.push_back(new MerkleNode(h));
        }

        vector<string> proof;
        while (nodes.size() > 1) {
            vector<MerkleNode*> newLevel;

            for (size_t i = 0; i < nodes.size(); i += 2) {
                if (i + 1 < nodes.size()) {
                    if (nodes[i]->hash == sha256(data)) {
                        proof.push_back(nodes[i + 1]->hash);
                    } else if (nodes[i + 1]->hash == sha256(data)) {
                        proof.push_back(nodes[i]->hash);
                    }
                    string combinedHash = sha256(nodes[i]->hash + nodes[i + 1]->hash);
                    MerkleNode* parent = new MerkleNode(combinedHash);
                    parent->left = nodes[i];
                    parent->right = nodes[i + 1];
                    newLevel.push_back(parent);
                } else {
                    newLevel.push_back(nodes[i]);
                }
            }
            nodes = newLevel;
        }

        return proof;
    }
};

// Main function to demonstrate the Merkle Tree
int main() {
    MerkleTree tree;
    vector<string> dataBlocks = {"block1", "block2", "block3", "block4"};

    // Build the Merkle Tree
    tree.build(dataBlocks);
    string rootHash = tree.getRootHash();
    cout << "Root Hash: " << rootHash << endl;

    // Verify a data block
    string dataToVerify = "block2";
    vector<string> proof = tree.generateProof(dataToVerify, dataBlocks);
    cout << "Proof for " << dataToVerify << ": ";
    for (const string& p : proof) {
        cout << p << " ";
    }
    cout << endl;

    bool isValid = tree.verifyData(dataToVerify, proof, rootHash);
    cout << "Verification result: " << (isValid ? "Valid" : "Invalid") << endl;

    return 0;
}
