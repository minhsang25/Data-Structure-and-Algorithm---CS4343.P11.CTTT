//STT: 25
//Full name: Le Minh Sang
//Homework

// Question 1. Implement a tree structure to represent a file system, where each node represents a file or
// directory. Allow users to navigate through the file system, create new files/directories, and
// delete existing ones.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Node class to represent files and directories
class Node {
public:
    string name;
    unordered_map<string, Node*> children; // For directories
    bool isFile;
    string content; // For files

    Node(string name, bool isFile = false) : name(name), isFile(isFile), content("") {}
};

// FileSystem class to manage the tree structure
class FileSystem {
private:
    Node* root;

    // Helper function to navigate to a node
    Node* navigateToNode(string path, bool createIfNotExists = false) {
        vector<string> dirs = split(path, '/');
        Node* current = root;
        for (const string& dir : dirs) {
            if (dir.empty()) continue;
            if (current->children.find(dir) == current->children.end()) {
                if (createIfNotExists) {
                    current->children[dir] = new Node(dir);
                } else {
                    return nullptr; // Path does not exist
                }
            }
            current = current->children[dir];
        }
        return current;
    }

    // Helper function to split paths
    vector<string> split(const string& path, char delimiter) {
        vector<string> result;
        string token;
        for (char c : path) {
            if (c == delimiter) {
                if (!token.empty()) result.push_back(token);
                token = "";
            } else {
                token += c;
            }
        }
        if (!token.empty()) result.push_back(token);
        return result;
    }

public:
    FileSystem() {
        root = new Node("/", false); // Root is always a directory
    }

    // List directory contents
    vector<string> ls(string path) {
        Node* node = navigateToNode(path);
        vector<string> result;
        if (node == nullptr) return result;
        if (node->isFile) {
            result.push_back(node->name); // If it's a file, return its name
        } else {
            for (const auto& child : node->children) {
                result.push_back(child.first);
            }
            sort(result.begin(), result.end());
        }
        return result;
    }

    // Create a directory
    void mkdir(string path) {
        navigateToNode(path, true);
    }

    // Add content to a file
    void addContentToFile(string filePath, string content) {
        Node* node = navigateToNode(filePath, true);
        node->isFile = true;
        node->content += content;
    }

    // Read content from a file
    string readContentFromFile(string filePath) {
        Node* node = navigateToNode(filePath);
        if (node == nullptr || !node->isFile) return "";
        return node->content;
    }

    // Delete a file or directory
    bool deleteNode(string path) {
        vector<string> dirs = split(path, '/');
        Node* current = root;
        Node* parent = nullptr;
        string targetName;

        // Traverse to the target node
        for (const string& dir : dirs) {
            if (dir.empty()) continue;
            if (current->children.find(dir) == current->children.end()) {
                return false; // Path does not exist
            }
            parent = current;
            current = current->children[dir];
            targetName = dir;
        }

        // Remove the node from its parent's children
        if (parent != nullptr) {
            parent->children.erase(targetName);
            delete current; // Free memory
            return true;
        }
        return false;
    }
};

// Main function to test the file system
int main() {
    FileSystem fs;

    // Create directories
    fs.mkdir("/a/b/c");
    fs.mkdir("/a/b/d");
    cout << "Contents of /a/b: ";
    for (const string& name : fs.ls("/a/b")) {
        cout << name << " ";
    }
    cout << endl;

    // Add files
    fs.addContentToFile("/a/b/c/file1.txt", "Hello");
    fs.addContentToFile("/a/b/c/file2.txt", "World");
    cout << "Contents of /a/b/c: ";
    for (const string& name : fs.ls("/a/b/c")) {
        cout << name << " ";
    }
    cout << endl;

    // Read file content
    cout << "Content of /a/b/c/file1.txt: " << fs.readContentFromFile("/a/b/c/file1.txt") << endl;

    // Delete a file
    fs.deleteNode("/a/b/c/file1.txt");
    cout << "Contents of /a/b/c after deletion: ";
    for (const string& name : fs.ls("/a/b/c")) {
        cout << name << " ";
    }
    cout << endl;

    return 0;
}
