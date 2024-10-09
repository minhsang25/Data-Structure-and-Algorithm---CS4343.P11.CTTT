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
    int maxSize;  // Stack limit
    int currentSize;  // Current number of elements

public:
    // Constructor to initialize the stack with a max size
    Stack(int size) {
        top = nullptr;
        maxSize = size;
        currentSize = 0;
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Function to check if the stack is full
    bool isFull() {
        return currentSize == maxSize;
    }

    // Function to push an element onto the stack
    void push(int value) {
        if (isFull()) {
            cout << "Stack is full." << endl;
            return;
        }
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = top;
        top = newNode;
        currentSize++;
        cout << value << " pushed to stack." << endl;
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
        currentSize--;
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
    int maxSize, choice, value;

    // Ask user for the stack's maximum size
    cout << "Enter the maximum size of the stack: ";
    cin >> maxSize;

    Stack stack(maxSize);  // Initialize stack with max size

    do {
        cout << "\nMenu: \n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Peek (Print top element)\n";
        cout << "4. Is Empty?\n";
        cout << "5. Is Full?\n";
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
            case 5:
                cout << (stack.isFull() ? "Stack is full." : "Stack is not full.") << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
