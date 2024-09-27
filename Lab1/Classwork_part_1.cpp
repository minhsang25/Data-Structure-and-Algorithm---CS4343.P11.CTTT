//SId: 22521240
//Full name: Le Minh Sang
//In-Class Exercise - Part 1,2

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* pnext;
};

class LinkedList {
public:
    Node* phead;
    Node* ptail;

    LinkedList() {
        phead = ptail = nullptr;
    }

    Node* CreateNode(int info) {
        if (info == 0) {
            return nullptr;
        }
        Node* temp = new Node;
        temp->data = info;
        temp->pnext = nullptr;
        return temp;
    }

    void AddNode(int info) {
        Node* temp = CreateNode(info);
        if (temp) { // Only add if the node is valid
            if (phead == nullptr) {
                phead = ptail = temp;
            } else {
                ptail->pnext = temp; 
                ptail = temp;
            }
        }
    }

    // Printing list
    void PrintList() {
        Node* temp = phead;
        if (phead == nullptr) {
            cout << "Empty list";
        } else {
            while (temp != nullptr) {
                cout << temp->data << " ";
                temp = temp->pnext;
            }
            cout << endl; 
        }
    }

    // Count the elements of the list
    int CountElm() {
        int cnt = 0;
        Node* temp = phead;
        while (temp != nullptr) {
            cnt++;
            temp = temp->pnext;
        }
        return cnt;
    }

    // q1: Find the middle node
    void MiddleNode() {
        Node* slow = phead;
        Node* fast = phead;
        Node* temp = nullptr;
        while (fast != nullptr && fast->pnext != nullptr) {
            temp = slow;
            slow = slow->pnext;
            fast = fast->pnext->pnext;
        }
        
        if (slow != nullptr) { 
            if (CountElm() % 2 == 0) {
                cout << "Middle elements: " << temp->data << ", " << slow->data << endl;
            } else {
                cout << "Middle Node: " << slow->data << endl;
            }
        }
    }

    // q2: Detect a cycle in a linked list
    void DetectCycle() {
        if (phead == nullptr || phead->pnext == nullptr) { 
            cout << "No cycle detected" << endl;
            return;
        }
        Node* slow = phead;
        Node* fast = phead;

        while (fast != nullptr && fast->pnext != nullptr) {
            slow = slow->pnext;
            fast = fast->pnext->pnext;
            if (slow == fast) {
                cout << "The list is cyclic" << endl;
                return;
            }
        }
        cout << "No cycle detected" << endl;
    }

    // q3: Combine two lists
    void CombineLists(LinkedList& otherList) {
        if (otherList.phead == nullptr) { // If the other list is empty, do nothing
            return;
        }
        if (phead == nullptr) { // If the current list is empty, just point it to the other list
            phead = otherList.phead;
            ptail = otherList.ptail;
        } else { // If both lists have elements
            ptail->pnext = otherList.phead; // Connect the tail of this list to the head of the other list
            ptail = otherList.ptail; // Update the tail to the tail of the other list
        }
    }

    // q6: Remove duplicate elements
    void RemoveDup() {
        if (phead == nullptr) return;
        Node* current = phead;
        while (current != nullptr && current->pnext != nullptr) {
            if (current->data == current->pnext->data) {
                Node* temp = current->pnext;
                current->pnext = current->pnext->pnext;
                delete temp;
            } else {
                current = current->pnext;
            }
        }
    }

    // q4: Find the intersection of two linked lists
    void Intersection(LinkedList& otherList) {
        if (phead == nullptr || otherList.phead == nullptr) {
            cout << "No intersection found" << endl;
            return;
        }

        Node* p1 = phead;
        Node* p2 = otherList.phead;

        cout << "Intersection elements: ";
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->data == p2->data) {
                cout << p1->data << " ";
                p1 = p1->pnext;
                p2 = p2->pnext;
            } else if (p1->data < p2->data) {
                p1 = p1->pnext;
            } else {
                p2 = p2->pnext;
            }
        }
        cout << endl;
    }

    //q5: Reverse the list

    void ReverseList() {
        Node* prev = nullptr;
        Node* current = phead;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->pnext;
            current->pnext = prev;
            prev = current;
            current = next;
        }
        phead = prev;
        cout << "List reversed." << endl;
    }
    

    // Destructor
    ~LinkedList() {
        Node* temp;
        while (phead != nullptr) {
            temp = phead;
            phead = phead->pnext;
            delete temp;
        }
    }
};

    //delete list
void ClearList(LinkedList& list) {
    Node* temp;
    while (list.phead != nullptr) {
        temp = list.phead;
        list.phead = list.phead->pnext;
        delete temp;
    }
    list.phead = list.ptail = nullptr; // Reset head and tail pointers
}

void InputList(LinkedList& list) {
    int data;
    while (true) {
        cin >> data;
        if (data == 0) break; // Stop when 0 is entered
        list.AddNode(data);
    }
}

int main() {
    int choose;
    LinkedList list1, list2;

    do {
        // Print the menu
        cout<<"SId: 22521240\nFull name: Le Minh Sang\nIn-Class Exercise - Part 1";
        cout << "\n1. Find the Middle Node of a Linked List\n";
        cout << "2. Detect a Cycle in a Linked List\n";
        cout << "3. Combine Two Sorted Linked Lists\n";
        cout << "4. Find the Intersection of Two Linked Lists\n";
        cout << "5. Reverse a Linked List\n";
        cout << "6. Eliminate Duplicates from a Sorted Linked List\n";
        cout << "7. Check if a Linked List is a Palindrome\n";
        cout << "8. Search node\n";
        cout << "9. Exit\n";
        cout << "Choose an option: ";
        cin >> choose;

        switch (choose) {
            case 1:
                cout << "Enter numbers to add to the list (0 to stop): " << endl;
                InputList(list1);
                list1.PrintList();
                list1.MiddleNode();
                break;
            case 2:
                cout << "Enter numbers to add to the list (0 to stop): " << endl;
                InputList(list1);
                list1.DetectCycle();
                break;
            case 3: //bug :))) 
                cout << "Enter numbers to add to list 1 (0 to stop): " << endl;
                InputList(list1);
                cout << "Enter numbers to add to list 2 (0 to stop): " << endl;
                InputList(list2);
                list1.CombineLists(list2);
                list1.PrintList();
                ClearList(list1);
                ClearList(list2);
                break;
            case 4: //bug :)))
                cout << "Enter numbers to add to list 1 (0 to stop): " << endl;
                InputList(list1);
                cout << "Enter numbers to add to list 2 (0 to stop): " << endl;
                InputList(list2);
                list1.Intersection(list2);
                break;
            case 5: //bug
                cout << "Enter numbers to add to the list (0 to stop): " << endl;
                InputList(list1);
                list1.ReverseList();
                list1.PrintList();
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
                break;
        }
    } while (choose != 9);
    system("pause");
    return 0;
}
//hello