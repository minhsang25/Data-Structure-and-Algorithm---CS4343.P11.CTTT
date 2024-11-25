//SId: 22521240
//Fullname: Le Minh Sang
//In-Class Exercise - Lab 4 - question 4

#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Define the Node structure for Linked List, Queue, and Stack
template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(T val) : data(val), next(nullptr) {}
};

// Linked List Implementation
template <typename T>
class LinkedList {
public:
    Node<T>* head;

    LinkedList() : head(nullptr) {}

    void append(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = newNode;
            return;
        }
        Node<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Bubble Sort for Linked List
    void bubbleSort() {
        if (!head) return;
        bool swapped;
        do {
            swapped = false;
            Node<T>* curr = head;
            while (curr && curr->next) {
                if (curr->data > curr->next->data) {
                    swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    // Insertion Sort for Linked List
    void insertionSort() {
        if (!head || !head->next) return;

        Node<T>* sorted = nullptr;
        Node<T>* curr = head;
        while (curr) {
            Node<T>* next = curr->next;
            if (!sorted || sorted->data >= curr->data) {
                curr->next = sorted;
                sorted = curr;
            } else {
                Node<T>* temp = sorted;
                while (temp->next && temp->next->data < curr->data) {
                    temp = temp->next;
                }
                curr->next = temp->next;
                temp->next = curr;
            }
            curr = next;
        }
        head = sorted;
    }

    // Selection Sort for Linked List
    void selectionSort() {
        if (!head) return;

        for (Node<T>* i = head; i != nullptr; i = i->next) {
            Node<T>* minNode = i;
            for (Node<T>* j = i->next; j != nullptr; j = j->next) {
                if (j->data < minNode->data) {
                    minNode = j;
                }
            }
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }
    }

    // Print Linked List
    void print() {
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Queue Implementation (using Linked List)
template <typename T>
class Queue {
public:
    Node<T>* front;
    Node<T>* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    T dequeue() {
        if (!front) throw runtime_error("Queue is empty");
        Node<T>* temp = front;
        T val = front->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    // Sorting Queue by copying to array, sorting, and then enqueuing back
    void bubbleSort() {
        // Extracting elements into an array
        Node<T>* temp = front;
        int count = 0;
        while (temp) {
            count++;
            temp = temp->next;
        }

        T* arr = new T[count];
        temp = front;
        for (int i = 0; temp; temp = temp->next, i++) {
            arr[i] = temp->data;
        }

        // Bubble Sort on array
        bool swapped;
        do {
            swapped = false;
            for (int i = 0; i < count - 1; ++i) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
        } while (swapped);

        // Enqueue sorted elements back into the queue
        for (int i = 0; i < count; ++i) {
            enqueue(arr[i]);
        }
        delete[] arr;
    }

    void print() {
        Node<T>* temp = front;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Stack Implementation (using Linked List)
template <typename T>
class Stack {
public:
    Node<T>* top;

    Stack() : top(nullptr) {}

    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
    }

    T pop() {
        if (!top) throw runtime_error("Stack is empty");
        Node<T>* temp = top;
        T val = top->data;
        top = top->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    // Sorting Stack by copying to array, sorting, and then pushing back
    void bubbleSort() {
        // Extracting elements into an array
        Node<T>* temp = top;
        int count = 0;
        while (temp) {
            count++;
            temp = temp->next;
        }

        T* arr = new T[count];
        temp = top;
        for (int i = 0; temp; temp = temp->next, i++) {
            arr[i] = temp->data;
        }

        // Bubble Sort on array
        bool swapped;
        do {
            swapped = false;
            for (int i = 0; i < count - 1; ++i) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
        } while (swapped);

        // Push sorted elements back into the stack
        for (int i = 0; i < count; ++i) {
            push(arr[i]);
        }
        delete[] arr;
    }

    void print() {
        Node<T>* temp = top;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Function to measure and print execution time
template <typename T>
long long measureSortTime(void (T::*sortFunc)(), T& container, const string& sortName) {
    auto start = high_resolution_clock::now();
    (container.*sortFunc)();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << sortName << " time: " << duration << " microseconds" << endl;
    return duration;
}

int main() {
    srand(time(0)); // Seed for random number generation

    int n = 100; // Test with 100 elements

    // Test Linked List
    LinkedList<int> linkedList;
    for (int i = 0; i < n; ++i) {
        linkedList.append(rand() % 10000);
    }
    cout << "Sorting Linked List:" << endl;
    measureSortTime(&LinkedList<int>::bubbleSort, linkedList, "Bubble Sort");
    measureSortTime(&LinkedList<int>::insertionSort, linkedList, "Insertion Sort");
    measureSortTime(&LinkedList<int>::selectionSort, linkedList, "Selection Sort");

    // Test Queue
    Queue<int> q;
    for (int i = 0; i < n; ++i) {
        q.enqueue(rand() % 10000);
    }
    cout << "\nSorting Queue:" << endl;
    measureSortTime(&Queue<int>::bubbleSort, q, "Bubble Sort");

    // Test Stack
    Stack<int> s;
    for (int i = 0; i < n; ++i) {
        s.push(rand() % 10000);
    }
    cout << "\nSorting Stack:" << endl;
    measureSortTime(&Stack<int>::bubbleSort, s, "Bubble Sort");

    return 0;
}
