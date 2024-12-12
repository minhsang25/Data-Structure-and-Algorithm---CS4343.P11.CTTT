//STT: 25
//Full name: Le Minh Sang

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            } else {
                q.push(current->left);
            }
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            } else {
                q.push(current->right);
            }
        }
    }

    void printTree() {
        if (root == nullptr) {
            cout << "Tree is empty" << endl;
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->value << " ";
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        cout << endl;
    }

    bool search(int value) {
        if (root == nullptr) {
            return false;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current->value == value) {
                return true;
            }
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        return false;
    }

    void deleteNode(int value) {
        if (root == nullptr) {
            return;
        }
        queue<Node*> q;
        q.push(root);
        Node* keyNode = nullptr;
        Node* current = nullptr;
        while (!q.empty()) {
            current = q.front();
            q.pop();
            if (current->value == value) {
                keyNode = current;
            }
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        if (keyNode != nullptr) {
            int x = current->value;
            deleteDeepestNode(current);
            keyNode->value = x;
        }
    }

    void deleteDeepestNode(Node* node) {
        queue<Node*> q;
        q.push(root);
        Node* current = nullptr;
        while (!q.empty()) {
            current = q.front();
            q.pop();
            if (current == node) {
                delete node;
                return;
            }
            if (current->right != nullptr) {
                if (current->right == node) {
                    delete node;
                    current->right = nullptr;
                    return;
                } else {
                    q.push(current->right);
                }
            }
            if (current->left != nullptr) {
                if (current->left == node) {
                    delete node;
                    current->left = nullptr;
                    return;
                } else {
                    q.push(current->left);
                }
            }
        }
    }
};

// Traversals
void preOrderTraversal(Node* root) {
    if (root != nullptr) {
        cout << root->value << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        cout << root->value << " ";
        inOrderTraversal(root->right);
    }
}

void postOrderTraversal(Node* root) {
    if (root != nullptr) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << root->value << " ";
    }
}

void levelOrderTraversal(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->value << " ";
        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

int main() {
    BinaryTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    cout << "Tree before deletion:" << endl;
    tree.printTree();

    cout << "Searching for 4: " << (tree.search(4) ? "Found" : "Not Found") << endl;

    tree.deleteNode(4);
    cout << "Tree after deletion of 4:" << endl;
    tree.printTree();

    cout << "Pre-order traversal: ";
    preOrderTraversal(tree.root);
    cout << endl;

    cout << "In-order traversal: ";
    inOrderTraversal(tree.root);
    cout << endl;

    cout << "Post-order traversal: ";
    postOrderTraversal(tree.root);
    cout << endl;

    cout << "Level-order traversal: ";
    levelOrderTraversal(tree.root);
    cout << endl;

    return 0;
}
