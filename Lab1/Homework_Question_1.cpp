#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string song;
    Node* next;
    Node* prev;
    Node(string songName) : song(songName), next(nullptr), prev(nullptr) {}
};

class MusicPlayer {
private:
    Node* head;
    Node* current;

public:
    MusicPlayer() : head(nullptr), current(nullptr) {}

    // Thêm bài hát vào cuối danh sách phát
    void addSong(string songName) {
        Node* newSong = new Node(songName);
        if (!head) {
            head = newSong;
            newSong->next = newSong;
            newSong->prev = newSong;
            current = head;
        } else {
            Node* tail = head->prev;
            tail->next = newSong;
            newSong->prev = tail;
            newSong->next = head;
            head->prev = newSong;
        }
    }

    // Chuyển sang bài hát tiếp theo và hiển thị
    void playNext() {
        if (current) {
            current = current->next;
            cout << current->song << endl;  // Hiển thị bài hát hiện tại sau khi chuyển
        }
    }

    // Chuyển sang bài hát trước đó và hiển thị
    void playPrev() {
        if (current) {
            current = current->prev;
            cout << current->song << endl;  // Hiển thị bài hát hiện tại sau khi chuyển
        }
    }

    // Xóa một bài hát theo tên
    void removeSong(string songName) {
        if (!head) return;

        Node* temp = head;
        do {
            if (temp->song == songName) {
                if (temp == head && temp->next == head) {
                    // Trường hợp chỉ có một bài hát trong danh sách
                    delete temp;
                    head = nullptr;
                    current = nullptr;
                    return;
                } else {
                    // Xóa bài hát
                    Node* prevNode = temp->prev;
                    Node* nextNode = temp->next;
                    prevNode->next = nextNode;
                    nextNode->prev = prevNode;

                    if (temp == head) head = nextNode;
                    if (temp == current) current = nextNode;

                    delete temp;
                    return;
                }
            }
            temp = temp->next;
        } while (temp != head);
    }

    // Hiển thị danh sách phát hiện tại
    void displayPlaylist() {
        if (!head) {
            cout << "Playlist is empty" << endl;
            return;
        }

        Node* temp = head;
        do {
            cout << temp->song << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
};

int main() {
    cout<<"SId: 22521240\nFullname: Le Minh Sang\nHomework - Lab 1";
    MusicPlayer player;
    int n;
    cin >> n;
    string command, song;

    for (int i = 0; i < n; i++) {
        cin >> command;
        if (command == "ADD") {
            cin >> song;
            player.addSong(song);
        } else if (command == "NEXT") {
            player.playNext();
        } else if (command == "PREV") {
            player.playPrev();
        } else if (command == "REMOVE") {
            cin >> song;
            player.removeSong(song);
        } else if (command == "DISPLAY") {
            player.displayPlaylist();
        }
    }

    return 0;
}
