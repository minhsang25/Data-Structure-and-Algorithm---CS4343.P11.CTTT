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

    // Add a song to the end of the playlist
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

    // Play next song (loop back to the first song if at the end)
    void playNext() {
        if (current) {
            current = current->next;
        }
    }

    // Play previous song (loop back to the last song if at the beginning)
    void playPrev() {
        if (current) {
            current = current->prev;
        }
    }

    // Remove a song by its name
    void removeSong(string songName) {
        if (!head) return;

        Node* temp = head;
        do {
            if (temp->song == songName) {
                if (temp == head && temp->next == head) {
                    // Only one song in the list
                    delete temp;
                    head = nullptr;
                    current = nullptr;
                    return;
                } else {
                    // Remove the song
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

    // Display the current playlist
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
