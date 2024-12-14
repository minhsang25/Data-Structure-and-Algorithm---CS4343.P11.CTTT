//STT: 25
//Full name: Le Minh Sang
//Homework

//Question 10. Tries are used for storing a dynamic set of strings where common prefixes are shared. They
//enable fast retrieval operations such as autocomplete and spell checking. Implement this tree.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Trie Node Class
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// Trie Class
class Trie {
private:
    TrieNode* root;

    // Helper function for autocomplete
    void findAllWords(TrieNode* node, string currentWord, vector<string>& results) {
        if (!node) return;

        if (node->isEndOfWord) {
            results.push_back(currentWord);
        }

        for (auto& child : node->children) {
            findAllWords(child.second, currentWord + child.first, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root; // Proper deletion can be expanded with recursive cleanup
    }

    // Insert a word into the Trie
    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    // Search for a word in the Trie
    bool search(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }

    // Check if any words start with a given prefix
    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return true;
    }

    // Autocomplete suggestions based on a prefix
    vector<string> autocomplete(const string& prefix) {
        vector<string> results;
        TrieNode* current = root;

        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return results; // No suggestions if prefix not found
            }
            current = current->children[c];
        }

        findAllWords(current, prefix, results);
        return results;
    }
};

// Main Function
int main() {
    Trie trie;

    // Insert words into the Trie
    trie.insert("apple");
    trie.insert("app");
    trie.insert("apricot");
    trie.insert("banana");
    trie.insert("bat");
    trie.insert("batman");
    trie.insert("cat");

    // Search for words
    cout << "Search Results:" << endl;
    cout << "Search for 'app': " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "Search for 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    cout << "Search for 'batman': " << (trie.search("batman") ? "Found" : "Not Found") << endl;
    cout << "Search for 'batmobile': " << (trie.search("batmobile") ? "Found" : "Not Found") << endl;

    // Check prefixes
    cout << "\nPrefix Check:" << endl;
    cout << "Prefix 'ap': " << (trie.startsWith("ap") ? "Exists" : "Doesn't Exist") << endl;
    cout << "Prefix 'bat': " << (trie.startsWith("bat") ? "Exists" : "Doesn't Exist") << endl;
    cout << "Prefix 'car': " << (trie.startsWith("car") ? "Exists" : "Doesn't Exist") << endl;

    // Autocomplete suggestions
    cout << "\nAutocomplete Suggestions for 'ap':" << endl;
    vector<string> suggestions = trie.autocomplete("ap");
    for (const string& suggestion : suggestions) {
        cout << suggestion << endl;
    }

    cout << "\nAutocomplete Suggestions for 'bat':" << endl;
    suggestions = trie.autocomplete("bat");
    for (const string& suggestion : suggestions) {
        cout << suggestion << endl;
    }

    return 0;
}
