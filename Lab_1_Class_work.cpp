//ID: 22521240
//FULL NAME: Le Minh Sang
//In-Class Exercise - Part 1

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
    
    LinkedList () {
        phead = ptail = nullptr;
    }

    // Node* CreateNode(int info) {
    //     Node* temp = new Node;
    //     temp->data = info;
    //     temp->pnext = nullptr;
    //     return temp;
    // }

    void AddNode(int info) {
        Node* temp = CreateNode(info);
        if (phead == nullptr) {
            phead = ptail = temp;
        } else {
            ptail->pnext = temp; 
            ptail = temp;
        }
    }
    void PrintList(){
        Node* temp = phead;
        if(phead == nullptr)
        {
            cout<<"Empty list";
        }
        else 
        {
            while(temp != nullptr)
            {   
                cout<<temp->data<<" ";
                temp = temp->pnext;
            }
        }
    }
    int CountElm (){
        int cnt =0;
        Node* temp = phead;
        while(temp != nullptr)
        {   
            temp = temp->pnext;
            cnt++;
        }
        return cnt;
    }

    int FindMiddleNode (){
        Node* temp = phead;
        int length = CountElm();
        int mid = length/2;
        int cnt = 0;
        while(temp != nullptr)
        {   
            if(length %2 !=0){
                if(cnt = mid){
                    cout<<temp->data<<" ";
                }
                else{
                    temp = temp->pnext; 
                    cnt++;
                }
            }
            else 
            {
                if(cnt = mid - 1||cnt = mid){
                    cout<<temp->data<<" ";
                }
                else{
                    temp = temp->pnext; 
                    cnt++;
                }
            }
        } 
    }

    void DetectCycle (){
        Node* slow = phead;
        Node* fast = phead;
        if(slow == fast){
            cout<<"This list is cycle";
        }
        else {
            cout<<"This list isn't cycle";
        }
    }

    void ReverseList() {
        Node* prev = nullptr;
        Node* curr = phead;
        Node* next = nullptr;
        while(curr != nullprt){
            next = curr->pnext;
            curr->pnext = prev;
            prev = curr;
            curr = next;
        }
        phead = prev;
        cout<<"Reversed list: ";
        PrintList();
    }

    void EliminateDuplicates() {
        if (phead == nullptr) return;
        Node* curr = phead;
        while(curr != nullptr && curr->pnext != nullptr){
            if(curr->data == curr->pnext->data){
                Node* temp = curr->pnext;
                curr->pnext = curr->pnext->pnext;
                delete temp;
            }
            else{
                curr = curr->pnext;
            }
        }
        cout<<"List after removing duplicates: ";
        PrintList();
    }

//chưa có câu 7

    void Search(int x){
        Node* temp = phead;
        while(temp != nullptr){
            if(temp->data == x){
                cout<<"Node with value "<<x<<" found at address: "<<temp<<endl;
                return temp;
            }
        }
        cout<<"Node with value "<<x<<" not found."<<end;
        return nullptr;    
    }
};

void Menu (){
    LinkedList list;
    int choice, value;
    do{
        cout<<"1. Find the Middle Node of a Linked List\n";
        cout<<"2. Detect the cycle in a linked list\n";
        cout<<"3. Combine Two Sorted Linked Lists\n";
        cout<<"4. Find the Intersection of Two Linked Lists\n";
        cout<<"5. Reverse a Linked List\n";
        cout<<"6. Eliminate Duplicates from a Sorted Linked List\n";
        cout<<"7. Check if a Linked List is a Palindrome\n";
        cout<<"8. Search node\n";
        cout<<"9. Exist.\n";
        switch (choice){
            case 1:
            
        }

    }
}

int main() {
    LinkedList list;

    
    Node* current = list.phead;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->pnext;
    }
    system("pause");
    return 0;
}

