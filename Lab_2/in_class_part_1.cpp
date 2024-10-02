#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

// Stack class
class Stack {
private:
    Node* top;

public:
    // Constructor to initialize the stack
    Stack() {
        top = nullptr;
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Function to push an element onto the stack
    void push(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    // Function to pop an element from the stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return -1;  // Return -1 if the stack is empty
        }
        Node* temp = top;
        int value = top->data;
        top = top->next;
        delete temp;
        return value;
    }

    // Function to get the top element of the stack
    int peek() {
        if (!isEmpty()) {
            return top->data;
        }
        cout << "Stack is empty." << endl;
        return -1;
    }

    // Function to display the top element of the stack
    void printTop() {
        if (!isEmpty()) {
            cout << "Top element: " << peek() << endl;
        } else {
            cout << "Stack is empty." << endl;
        }
    }
};

// Main menu for stack operations
int main() {
    Stack stack;
    int choice, value;

    do {
        cout << "\nMenu: \n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Peek\n";
        cout << "4. Is Empty?\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> value;
                stack.push(value);
                break;
            case 2:
                cout << "Popped value: " << stack.pop() << endl;
                break;
            case 3:
                stack.printTop();
                break;
            case 4:
                cout << (stack.isEmpty() ? "Stack is empty." : "Stack is not empty.") << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
