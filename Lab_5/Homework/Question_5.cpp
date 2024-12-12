//STT: 25
//Full name: Le Minh Sang
//Homework

//Question 5. Create an expression parser that converts infix expressions into syntax trees (abstract syntax
// trees) and evaluates them. Support basic arithmetic operations.
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <stdexcept>

using namespace std;

// Node for the Abstract Syntax Tree (AST)
class ExprNode {
public:
    string value;
    ExprNode* left;
    ExprNode* right;

    ExprNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Expression Parser Class
class ExpressionParser {
private:
    // Check if a character is an operator
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    // Get the precedence of an operator
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    // Convert infix expression to postfix (Reverse Polish Notation)
    string infixToPostfix(const string& infix) {
        string postfix = "";
        stack<char> operators;

        for (size_t i = 0; i < infix.size(); i++) {
            char c = infix[i];

            // Skip whitespace
            if (isspace(c)) continue;

            if (isdigit(c)) {
                // Append numbers directly to postfix
                while (i < infix.size() && (isdigit(infix[i]) || infix[i] == '.')) {
                    postfix += infix[i];
                    i++;
                }
                postfix += " ";
                i--;
            } else if (isOperator(c)) {
                // Pop operators with higher or equal precedence
                while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                    postfix += operators.top();
                    postfix += " ";
                    operators.pop();
                }
                operators.push(c);
            } else if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                // Pop until '(' is found
                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    postfix += " ";
                    operators.pop();
                }
                if (!operators.empty() && operators.top() == '(') operators.pop();
            }
        }

        // Pop any remaining operators
        while (!operators.empty()) {
            postfix += operators.top();
            postfix += " ";
            operators.pop();
        }

        return postfix;
    }

    // Build the Abstract Syntax Tree (AST) from postfix expression
    ExprNode* buildAST(const string& postfix) {
        stack<ExprNode*> nodeStack;
        string token = "";

        for (size_t i = 0; i < postfix.size(); i++) {
            char c = postfix[i];

            if (isspace(c)) {
                if (!token.empty()) {
                    nodeStack.push(new ExprNode(token));
                    token = "";
                }
            } else if (isOperator(c)) {
                ExprNode* right = nodeStack.top(); nodeStack.pop();
                ExprNode* left = nodeStack.top(); nodeStack.pop();
                ExprNode* node = new ExprNode(string(1, c));
                node->left = left;
                node->right = right;
                nodeStack.push(node);
            } else {
                token += c;
            }
        }

        return nodeStack.top();
    }

    // Evaluate the AST
    double evaluateAST(ExprNode* node) {
        if (!node->left && !node->right) {
            return stod(node->value); // Leaf node is a number
        }

        double leftValue = evaluateAST(node->left);
        double rightValue = evaluateAST(node->right);

        if (node->value == "+") return leftValue + rightValue;
        if (node->value == "-") return leftValue - rightValue;
        if (node->value == "*") return leftValue * rightValue;
        if (node->value == "/") {
            if (rightValue == 0) throw runtime_error("Division by zero!");
            return leftValue / rightValue;
        }

        throw runtime_error("Invalid operator: " + node->value);
    }

    // Print the AST (in-order traversal)
    void printAST(ExprNode* node) {
        if (!node) return;
        if (node->left) cout << "(";
        printAST(node->left);
        cout << node->value;
        printAST(node->right);
        if (node->right) cout << ")";
    }

public:
    // Parse and evaluate an infix expression
    double parseAndEvaluate(const string& expression) {
        string postfix = infixToPostfix(expression);
        ExprNode* root = buildAST(postfix);
        cout << "AST Representation: ";
        printAST(root);
        cout << endl;
        return evaluateAST(root);
    }
};

// Main function to demonstrate the expression parser
int main() {
    ExpressionParser parser;

    string expression;
    cout << "Enter an arithmetic expression (e.g., (3 + 5) * 2): ";
    getline(cin, expression);

    try {
        double result = parser.parseAndEvaluate(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
