//SId: 22521240
//Fullname: Le Minh Sang
//In-Class Exercise - Lab 2 - Part 2

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
    int maxSize;    // Maximum size of the queue
    int currentSize; // Current number of elements in the queue

public:
    // Constructor to initialize the queue with a maximum size
    Queue(int size) {
        front = rear = nullptr;
        maxSize = size;
        currentSize = 0;
    }

    // Function to check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Function to check if the queue is full
    bool isFull() {
        return currentSize == maxSize;
    }

    // Function to enqueue an element into the queue
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full." << endl;
            return;
        }
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        currentSize++;
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
        currentSize--;
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
    cout<<"SId: 22521240\nFullname: Le Minh Sang\nHomework - Lab 2 - Question 1\n";
    int maxSize, choice, value;

    // Ask user for the queue's maximum size
    cout << "Enter the maximum size of the queue: ";
    cin >> maxSize;

    Queue queue(maxSize);  // Initialize queue with max size

    do {
        cout << "\nMenu: \n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Print Front and Rear\n";
        cout << "4. Is Empty?\n";
        cout << "5. Is Full?\n";
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
            case 5:
                cout << (queue.isFull() ? "Queue is full." : "Queue is not full.") << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
