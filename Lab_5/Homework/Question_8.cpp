//STT: 25
//Full name: Le Minh Sang
//Homework

//Question 8. Merkle trees are used in blockchain to verify the integrity of data blocks efficiently by storing
// hashes of transactions in a hierarchical structure. Implement this tree in blockchain.

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <openssl/sha.h>

using namespace std;

// Utility function to compute SHA-256 hash of a string
string computeHash(const string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data.c_str(), data.size(), hash);

    // Convert hash to a hexadecimal string
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Node class for the Merkle Tree
class MerkleNode {
public:
    string hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(const string& hash) : hash(hash), left(nullptr), right(nullptr) {}
};

// Merkle Tree class
class MerkleTree {
private:
    MerkleNode* root;

    // Helper function to build the tree recursively
    MerkleNode* buildTree(vector<MerkleNode*>& nodes) {
        if (nodes.size() == 1) {
            return nodes[0];
        }

        vector<MerkleNode*> parentNodes;
        for (size_t i = 0; i < nodes.size(); i += 2) {
            MerkleNode* left = nodes[i];
            MerkleNode* right = (i + 1 < nodes.size()) ? nodes[i + 1] : nullptr;

            string combinedHash = left->hash;
            if (right) {
                combinedHash += right->hash;
            }
            string parentHash = computeHash(combinedHash);
            MerkleNode* parentNode = new MerkleNode(parentHash);
            parentNode->left = left;
            parentNode->right = right;
            parentNodes.push_back(parentNode);
        }

        return buildTree(parentNodes);
    }

    // Recursive helper to delete tree nodes
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
        if (dataBlocks.empty()) {
            root = nullptr;
            return;
        }

        vector<MerkleNode*> nodes;
        for (const string& data : dataBlocks) {
            nodes.push_back(new MerkleNode(computeHash(data)));
        }

        root = buildTree(nodes);
    }

    // Get the root hash of the Merkle Tree
    string getRootHash() {
        return root ? root->hash : "";
    }

    // Verify the integrity of a data block given its hash and a proof path
    bool verifyData(const string& dataHash, const vector<string>& proof, const string& rootHash) {
        string currentHash = dataHash;

        for (const string& proofHash : proof) {
            currentHash = computeHash(currentHash + proofHash);
        }

        return currentHash == rootHash;
    }
};

// Main function to demonstrate Merkle Tree usage
int main() {
    MerkleTree merkleTree;

    // Data blocks
    vector<string> dataBlocks = {
        "Transaction1",
        "Transaction2",
        "Transaction3",
        "Transaction4"
    };

    // Build the Merkle Tree
    merkleTree.build(dataBlocks);

    // Display the root hash
    string rootHash = merkleTree.getRootHash();
    cout << "Root Hash: " << rootHash << endl;

    // Verify a data block
    string dataHash = computeHash("Transaction1");
    vector<string> proof = {computeHash("Transaction2"), computeHash(computeHash("Transaction3") + computeHash("Transaction4"))};

    bool isVerified = merkleTree.verifyData(dataHash, proof, rootHash);
    cout << "Verification Result: " << (isVerified ? "Valid" : "Invalid") << endl;

    return 0;
}


