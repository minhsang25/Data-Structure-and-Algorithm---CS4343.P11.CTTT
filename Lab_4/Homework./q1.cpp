//SId: 22521240
//Fullname: Le Minh Sang
//Homework Exercise - Lab 4
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Structures for different data types
struct Product {
    string name;
    float price;
    int rating;
    int popularity;
};

struct Post {
    string content;
    int likes;
    int comments;
    int shares;
    time_t time_posted;
};

struct Student {
    string name;
    int grade;
    int age;
};

struct Song {
    string title;
    string artist;
    string genre;
    int mood; // A simplified mood score
};

// Sorting functions
template <typename T>
void quickSort(T arr[], int low, int high);

template <typename T>
int partition(T arr[], int low, int high);

template <typename T>
void mergeSort(T arr[], int left, int right);

template <typename T>
void merge(T arr[], int left, int mid, int right);

template <typename T>
void insertionSort(T arr[], int n);

// Exercise functions
void sortProducts();
void sortPosts();
void sortStudents();
void sortSongs();

// Utility functions
void displayMenu();
void performSortChoice(int choice);

int main() {
    srand(time(0));
    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice >= 1 && choice <= 4) {
            performSortChoice(choice);
        } else if (choice != 0) {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    cout << "Program exited.\n";
    return 0;
}

void displayMenu() {
    cout << "\nSorting Exercises Menu:\n";
    cout << "1. Sort Products (E-commerce website)\n";
    cout << "2. Sort Social Media Posts\n";
    cout << "3. Sort Students (School Management)\n";
    cout << "4. Sort Songs (Music Playlist)\n";
    cout << "0. Exit\n";
}

// Exercise implementations
void performSortChoice(int choice) {
    switch (choice) {
        case 1:
            sortProducts();
            break;
        case 2:
            sortPosts();
            break;
        case 3:
            sortStudents();
            break;
        case 4:
            sortSongs();
            break;
    }
}

// Sorting product listings by price using Quick Sort
void sortProducts() {
    const int n = 10;
    Product products[n];
    for (int i = 0; i < n; i++) {
        products[i] = {"Product" + to_string(i + 1), (float)(rand() % 100), rand() % 5, rand() % 100};
    }
    quickSort(products, 0, n - 1); // Sorting by price
    cout << "Products sorted by price:\n";
    for (const auto& product : products) {
        cout << "Name: " << product.name << ", Price: $" << product.price << "\n";
    }
}

// Sorting posts by likes using Quick Sort
void sortPosts() {
    const int n = 10;
    Post posts[n];
    for (int i = 0; i < n; i++) {
        posts[i] = {"Post " + to_string(i + 1), rand() % 100, rand() % 50, rand() % 20, time(0)};
    }
    quickSort(posts, 0, n - 1); // Sorting by likes
    cout << "Posts sorted by likes:\n";
    for (const auto& post : posts) {
        cout << "Content: " << post.content << ", Likes: " << post.likes << "\n";
    }
}

// Sorting students by grade using Merge Sort
void sortStudents() {
    const int n = 10;
    Student students[n];
    for (int i = 0; i < n; i++) {
        students[i] = {"Student " + to_string(i + 1), rand() % 100, rand() % 18 + 10};
    }
    mergeSort(students, 0, n - 1); // Sorting by grade
    cout << "Students sorted by grade:\n";
    for (const auto& student : students) {
        cout << "Name: " << student.name << ", Grade: " << student.grade << "\n";
    }
}

// Sorting songs by mood using Insertion Sort
void sortSongs() {
    const int n = 10;
    Song songs[n];
    for (int i = 0; i < n; i++) {
        songs[i] = {"Song " + to_string(i + 1), "Artist " + to_string(i + 1), "Genre" + to_string(rand() % 5), rand() % 10};
    }
    insertionSort(songs, n); // Sorting by mood
    cout << "Songs sorted by mood:\n";
    for (const auto& song : songs) {
        cout << "Title: " << song.title << ", Mood: " << song.mood << "\n";
    }
}

// Quick Sort specialized for Product sorting by price
template <>
int partition<Product>(Product arr[], int low, int high) {
    Product pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].price < pivot.price) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort specialized for Post sorting by likes
template <>
int partition<Post>(Post arr[], int low, int high) {
    Post pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].likes < pivot.likes) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Generic Quick Sort
template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort for Student sorting by grade
template <typename T>
void mergeSort(T arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template <typename T>
void merge(T arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    T* L = new T[n1];
    T* R = new T[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].grade <= R[j].grade) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

// Insertion Sort for Songs by mood
template <typename T>
void insertionSort(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].mood > key.mood) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
