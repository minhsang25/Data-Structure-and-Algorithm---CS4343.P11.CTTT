#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* pnext;
    Node(int info) : data(info), pnext(nullptr) {}
};

class LinkedList {
public:
    Node* phead;
    Node* ptail;

    LinkedList() {
        phead = ptail = nullptr;
    }

    Node* CreateNode(int info) {
        return new Node(info);
    }

    void AddNode(int info) {
        Node* temp = CreateNode(info);
        if (phead == nullptr) {
            phead = ptail = temp;
        } else {
            ptail->pnext = temp;
            ptail = temp;
        }
    }

    void PrintList() {
        Node* temp = phead;
        if (phead == nullptr) {
            cout << "Empty list" << endl;
        } else {
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->pnext;
            }
            cout << endl;
        }
    }

    int CountElm() {
        int cnt = 0;
        Node* temp = phead;
        while (temp != nullptr) {
            temp = temp->pnext;
            cnt++;
        }
        return cnt;
    }

    void FindMiddleNode() {
        int length = CountElm();
        int mid = length / 2;
        Node* temp = phead;
        int cnt = 0;
        while (temp != nullptr) {
            if (cnt == mid) {
                cout << "Middle node: " << temp->data << endl;
                break;
            }
            temp = temp->pnext;
            cnt++;
        }
    }

    void DetectCycle() {
        Node* slow = phead;
        Node* fast = phead;
        while (fast != nullptr && fast->pnext != nullptr) {
            slow = slow->pnext;
            fast = fast->pnext->pnext;
            if (slow == fast) {
                cout << "This list is circular." << endl;
                return;
            }
        }
        cout << "This list isn't circular." << endl;
    }

    void ReverseList() {
        Node* prev = nullptr;
        Node* curr = phead;
        Node* next = nullptr;
        while (curr != nullptr) {
            next = curr->pnext;
            curr->pnext = prev;
            prev = curr;
            curr = next;
        }
        phead = prev;
        cout << "Reversed list: ";
        PrintList();
    }

    void EliminateDuplicates() {
        if (phead == nullptr) return;
        Node* curr = phead;
        while (curr != nullptr && curr->pnext != nullptr) {
            if (curr->data == curr->pnext->data) {
                Node* temp = curr->pnext;
                curr->pnext = curr->pnext->pnext;
                delete temp;
            } else {
                curr = curr->pnext;
            }
        }
        cout << "List after removing duplicates: ";
        PrintList();
    }

    bool IsPalindrome() {
        if (phead == nullptr || phead->pnext == nullptr) return true;

        // Find the middle of the list
        Node* slow = phead;
        Node* fast = phead;
        Node* prev_of_slow = nullptr;

        while (fast != nullptr && fast->pnext != nullptr) {
            fast = fast->pnext->pnext;
            prev_of_slow = slow;
            slow = slow->pnext;
        }

        Node* second_half = slow;
        prev_of_slow->pnext = nullptr;

        Node* prev = nullptr;
        Node* curr = second_half;
        Node* next = nullptr;

        // Reverse the second half of the list
        while (curr != nullptr) {
            next = curr->pnext;
            curr->pnext = prev;
            prev = curr;
            curr = next;
        }
        second_half = prev;

        // Compare the first and second half
        Node* first_half = phead;
        while (second_half != nullptr) {
            if (first_half->data != second_half->data) {
                cout << "List is not a palindrome." << endl;
                return false;
            }
            first_half = first_half->pnext;
            second_half = second_half->pnext;
        }
        cout << "List is a palindrome." << endl;
        return true;
    }

    Node* Search(int x) {
        Node* temp = phead;
        while (temp != nullptr) {
            if (temp->data == x) {
                cout << "Node with value " << x << " found at address: " << temp << endl;
                return temp;
            }
            temp = temp->pnext;
        }
        cout << "Node with value " << x << " not found." << endl;
        return nullptr;
    }
};

void Menu() {
    LinkedList list;
    int choice, value;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add Node\n";
        cout << "2. Print List\n";
        cout << "3. Find the Middle Node\n";
        cout << "4. Detect Cycle\n";
        cout << "5. Reverse List\n";
        cout << "6. Eliminate Duplicates\n";
        cout << "7. Check if List is Palindrome\n";
        cout << "8. Search Node\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to add: ";
                cin >> value;
                list.AddNode(value);
                break;
            case 2:
                list.PrintList();
                break;
            case 3:
                list.FindMiddleNode();
                break;
            case 4:
                list.DetectCycle();
                break;
            case 5:
                list.ReverseList();
                break;
            case 6:
                list.EliminateDuplicates();
                break;
            case 7:
                list.IsPalindrome();
                break;
            case 8:
                cout << "Enter value to search: ";
                cin >> value;
                list.Search(value);
                break;
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 9);
}

int main() {
    Menu();
    return 0;
}

//hello
