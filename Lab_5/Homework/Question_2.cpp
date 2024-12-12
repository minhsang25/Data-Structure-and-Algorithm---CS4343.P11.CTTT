//STT: 25
//Full name: Le Minh Sang
//Homework

// Question 2. Create a parser that reads an XML or HTML document and constructs a tree structure
// representing its elements. Implement methods to query specific elements or attributes from
// the tree.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <sstream>

using namespace std;

// Class to represent a node in the XML/HTML tree
class ElementNode {
public:
    string tagName;
    unordered_map<string, string> attributes;
    vector<ElementNode*> children;
    string innerText;

    ElementNode(string tag) : tagName(tag), innerText("") {}

    ~ElementNode() {
        for (ElementNode* child : children) {
            delete child;
        }
    }
};

// Class to parse and manage an XML/HTML tree
class XmlParser {
private:
    ElementNode* root;

    // Helper function to parse attributes
    unordered_map<string, string> parseAttributes(const string& tagContent) {
        unordered_map<string, string> attributes;
        istringstream stream(tagContent);
        string key, value;
        while (stream >> key) {
            size_t equalPos = key.find('=');
            if (equalPos != string::npos) {
                value = key.substr(equalPos + 1);
                key = key.substr(0, equalPos);
                if (value.front() == '\"' && value.back() == '\"') {
                    value = value.substr(1, value.size() - 2); // Remove quotes
                }
                attributes[key] = value;
            }
        }
        return attributes;
    }

    // Helper function to parse a tag
    string parseTag(const string& line, unordered_map<string, string>& attributes) {
        size_t spacePos = line.find(' ');
        if (spacePos != string::npos) {
            string tagName = line.substr(0, spacePos);
            attributes = parseAttributes(line.substr(spacePos + 1));
            return tagName;
        }
        return line;
    }

public:
    XmlParser() : root(nullptr) {}

    ~XmlParser() {
        delete root;
    }

    // Parse the XML/HTML content
    void parse(const string& content) {
        stack<ElementNode*> nodeStack;
        istringstream stream(content);
        string line;

        while (getline(stream, line)) {
            line.erase(remove(line.begin(), line.end(), '\t'), line.end()); // Remove tabs
            line.erase(remove(line.begin(), line.end(), ' '), line.end()); // Remove spaces

            if (line.empty()) continue;

            if (line[0] == '<' && line[1] != '/') { // Opening tag
                size_t closeBracket = line.find('>');
                string tagContent = line.substr(1, closeBracket - 1);
                unordered_map<string, string> attributes;
                string tagName = parseTag(tagContent, attributes);

                ElementNode* newNode = new ElementNode(tagName);
                newNode->attributes = attributes;

                if (!nodeStack.empty()) {
                    nodeStack.top()->children.push_back(newNode);
                } else {
                    root = newNode; // First tag is the root
                }

                nodeStack.push(newNode);
            } else if (line[0] == '<' && line[1] == '/') { // Closing tag
                nodeStack.pop();
            } else { // Inner text
                if (!nodeStack.empty()) {
                    nodeStack.top()->innerText += line;
                }
            }
        }
    }

    // Query elements by tag name
    vector<ElementNode*> queryByTagName(const string& tagName) {
        vector<ElementNode*> results;
        queryByTagNameHelper(root, tagName, results);
        return results;
    }

    void queryByTagNameHelper(ElementNode* node, const string& tagName, vector<ElementNode*>& results) {
        if (!node) return;
        if (node->tagName == tagName) {
            results.push_back(node);
        }
        for (ElementNode* child : node->children) {
            queryByTagNameHelper(child, tagName, results);
        }
    }

    // Print the tree structure
    void printTree(ElementNode* node, int depth = 0) {
        if (!node) return;
        cout << string(depth * 2, ' ') << "<" << node->tagName;

        for (const auto& attr : node->attributes) {
            cout << " " << attr.first << "=\"" << attr.second << "\"";
        }

        cout << ">";
        if (!node->innerText.empty()) {
            cout << node->innerText;
        }
        cout << endl;

        for (ElementNode* child : node->children) {
            printTree(child, depth + 1);
        }

        cout << string(depth * 2, ' ') << "</" << node->tagName << ">" << endl;
    }

    void printTree() {
        printTree(root);
    }
};

// Main function to demonstrate XML/HTML parsing
int main() {
    string content = R"(
        <html>
            <head>
                <title>Sample Document</title>
            </head>
            <body>
                <div id="main" class="container">
                    <h1>Welcome</h1>
                    <p>This is a sample paragraph.</p>
                </div>
            </body>
        </html>
    )";

    XmlParser parser;
    parser.parse(content);

    // Print the parsed tree
    cout << "Parsed XML/HTML Tree:" << endl;
    parser.printTree();

    // Query elements by tag name
    string queryTag = "div";
    cout << "\nQuerying elements with tag name: " << queryTag << endl;
    vector<ElementNode*> results = parser.queryByTagName(queryTag);
    for (ElementNode* node : results) {
        cout << "<" << node->tagName << ">" << endl;
    }

    return 0;
}
