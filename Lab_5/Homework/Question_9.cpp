
//STT: 25
//Full name: Le Minh Sang
//Homework

//Question 9. Phylogenetic trees represent evolutionary relationships between species or genes based on genetic data. They help researchers understand biodiversity and evolutionary history. Implement this tree.
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <iomanip>
#include <cmath>

using namespace std;

// Node class for the Phylogenetic Tree
class PhylogeneticNode {
public:
    string name;
    PhylogeneticNode* left;
    PhylogeneticNode* right;
    double distance;

    PhylogeneticNode(string name, double distance = 0.0)
        : name(name), left(nullptr), right(nullptr), distance(distance) {}
};

// Helper function to calculate distance between clusters (UPGMA)
vector<vector<double>> calculateNewDistanceMatrix(const vector<vector<double>>& matrix, int idx1, int idx2) {
    int size = matrix.size();
    vector<vector<double>> newMatrix(size - 1, vector<double>(size - 1));

    int newRow = 0, newCol = 0;
    for (int i = 0; i < size; i++) {
        if (i == idx1 || i == idx2) continue;

        newCol = 0;
        for (int j = 0; j < size; j++) {
            if (j == idx1 || j == idx2) continue;

            newMatrix[newRow][newCol] = matrix[i][j];
            newCol++;
        }

        newRow++;
    }

    for (int i = 0; i < size; i++) {
        if (i == idx1 || i == idx2) continue;

        int smaller = min(idx1, idx2);
        int larger = max(idx1, idx2);
        double avgDistance = (matrix[i][smaller] + matrix[i][larger]) / 2.0;

        newMatrix[newMatrix.size() - 1][newCol] = avgDistance;
        newMatrix[newCol][newMatrix.size() - 1] = avgDistance;
    }

    return newMatrix;
}

// Phylogenetic Tree class
class PhylogeneticTree {
private:
    PhylogeneticNode* root;

    // Helper function for displaying the tree
    void displayTreeHelper(PhylogeneticNode* node, int depth) {
        if (!node) return;
        displayTreeHelper(node->right, depth + 1);
        cout << string(depth * 4, ' ') << node->name << " (" << node->distance << ")" << endl;
        displayTreeHelper(node->left, depth + 1);
    }

public:
    PhylogeneticTree() : root(nullptr) {}

    ~PhylogeneticTree() {
        // TODO: Implement cleanup of allocated memory
    }

    // Build the tree using a simple clustering method
    void buildTree(const vector<string>& species, const vector<vector<double>>& distanceMatrix) {
        if (species.size() != distanceMatrix.size() || species.empty()) {
            cerr << "Invalid input for species or distance matrix." << endl;
            return;
        }

        vector<PhylogeneticNode*> nodes;
        for (const string& sp : species) {
            nodes.push_back(new PhylogeneticNode(sp));
        }

        vector<vector<double>> matrix = distanceMatrix;

        while (nodes.size() > 1) {
            // Find the closest pair
            int idx1 = 0, idx2 = 1;
            double minDistance = matrix[0][1];

            for (int i = 0; i < matrix.size(); i++) {
                for (int j = i + 1; j < matrix.size(); j++) {
                    if (matrix[i][j] < minDistance) {
                        minDistance = matrix[i][j];
                        idx1 = i;
                        idx2 = j;
                    }
                }
            }

            // Create a new node combining the two closest nodes
            PhylogeneticNode* newNode = new PhylogeneticNode(
                "(" + nodes[idx1]->name + ", " + nodes[idx2]->name + ")",
                minDistance / 2.0
            );
            newNode->left = nodes[idx1];
            newNode->right = nodes[idx2];

            // Update the node list and distance matrix
            nodes.erase(nodes.begin() + max(idx1, idx2));
            nodes.erase(nodes.begin() + min(idx1, idx2));
            nodes.push_back(newNode);

            matrix = calculateNewDistanceMatrix(matrix, idx1, idx2);
        }

        root = nodes[0];
    }

    // Display the tree
    void displayTree() {
        if (!root) {
            cout << "The phylogenetic tree is empty." << endl;
            return;
        }
        displayTreeHelper(root, 0);
    }
};

// Main function to demonstrate the Phylogenetic Tree
int main() {
    // Example species and their distance matrix
    vector<string> species = {"A", "B", "C", "D"};
    vector<vector<double>> distanceMatrix = {
        {0.0, 2.0, 4.0, 6.0},
        {2.0, 0.0, 4.0, 6.0},
        {4.0, 4.0, 0.0, 6.0},
        {6.0, 6.0, 6.0, 0.0}
    };

    PhylogeneticTree tree;
    tree.buildTree(species, distanceMatrix);

    cout << "Phylogenetic Tree:" << endl;
    tree.displayTree();

    return 0;
}
