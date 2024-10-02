#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

// Queue class
class Queue {
private:
    Node* front;
    Node* rear;

public:
    // Constructor to initialize the queue
    Queue() {
        front = rear = nullptr;
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Function to enqueue an element into the queue
    void enqueue(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // Function to dequeue an element from the queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;  // Return -1 if the queue is empty
        }
        Node* temp = front;
        int value = front->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;  // If the queue is now empty, set rear to nullptr
        }
        delete temp;
        return value;
    }

    // Function to print front and rear elements
    void printFrontRear() {
        if (!isEmpty()) {
            cout << "Front element: " << front->data << endl;
            cout << "Rear element: " << rear->data << endl;
        } else {
            cout << "Queue is empty." << endl;
        }
    }
};

// Main menu for queue operations
int main() {
    Queue queue;
    int choice, value;

    do {
        cout << "\nMenu: \n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Print Front and Rear\n";
        cout << "4. Is Empty?\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                queue.enqueue(value);
                break;
            case 2:
                cout << "Dequeued value: " << queue.dequeue() << endl;
                break;
            case 3:
                queue.printFrontRear();
                break;
            case 4:
                cout << (queue.isEmpty() ? "Queue is empty." : "Queue is not empty.") << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
