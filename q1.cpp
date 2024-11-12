// Implement each sorting algorithm to sort a list containing 1K random integers. Measure the execution time and compare the performance of the algorithms
// Each sorting algorithm including buble sort, selection sort, insertion sort, binary insertion sort, quick sort, merge sort, heap sort

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
// Function to generate 1K random integers
vector<int> generateRandomList(int n)
{
    vector<int> list;
    for (int i = 0; i < n; i++)
    {
        list.push_back(rand() % 1000 + 1);
    }
    return list;
}
// Function to print the list
void printList(vector<int> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i] << " ";
    }
    cout << endl;
}
// Function to swap two elements
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
// Bubble sort algorithm
void bubbleSort(vector<int> &list)
{
    int n = list.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)

            if (list[j] > list[j + 1])
                swap(list[j], list[j + 1]);
    }
}
// Selection sort algorithm
void selectionSort(vector<int> &list)
{
    int n = list.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (list[j] < list[minIndex])
                minIndex = j;
        }
        swap(list[minIndex], list[i]);
    }
}
// Insertion sort algorithm
void insertionSort(vector<int> &list)
{
    int n = list.size();
    for (int i = 1; i < n; i++)
    {
        int key = list[i];
        int j = i - 1;

        while (j >= 0 && list[j] > key)
        {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}
// Binary insertion sort algorithm
void binaryInsertionSort(vector<int> &list)
{
    int n = list.size();
    for (int i = 1; i < n; i++)
    {
        int key = list[i];
        int left = 0;
        int right = i - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (key < list[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
        for (int j = i - 1; j >= left; j--)
        {
            list[j + 1] = list[j];
        }
        list[left] = key;
    }
}
// Quick sort algorithm
int partition(vector<int> &list, int low, int high)
{
    int pivot = list[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (list[j] < pivot)
        {
            i++;
            swap(list[i], list[j]);
        }
    }
    swap(list[i + 1], list[high]);
    return i + 1;
}
void quickSort(vector<int> &list, int low, int high)
{
    if (low < high)
    {
        int pi = partition(list, low, high);
        quickSort(list, low, pi - 1);
        quickSort(list, pi + 1, high);
    }
}
// Merge sort algorithm
void merge(vector<int> &list, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = list[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = list[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            list[k] = L[i++];
        else
            list[k] = R[j++];
        k++;
    }
    while (i < n1)
        list[k++] = L[i++];
    while (j < n2)
        list[k++] = R[j++];
}
// Function to merge sort
void mergeSort(vector<int> &list, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}
// Heap sort algorithm
void heapify(vector<int> &list, int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && list[i] < list[l])
        largest = l;
    if (r < n && list[largest] < list[r])
        largest = r;
    if (largest != i)
    {
        swap(list[i], list[largest]);
        heapify(list, n, largest);
    }
}
void heapSort(vector<int> &list)
{
    int n = list.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(list, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        swap(list[0], list[i]);
        heapify(list, i, 0);
    }
}
// Function to measure the execution time of each sorting algorithm
void measureExecutionTime(vector<int> list, string algorithm)
{
    auto start = chrono::high_resolution_clock::now();
    if (algorithm == "bubbleSort")
        bubbleSort(list);
    else if (algorithm == "selectionSort")
        selectionSort(list);
    else if (algorithm == "insertionSort")
        insertionSort(list);
    else if (algorithm == "binaryInsertionSort")
        binaryInsertionSort(list);
    else if (algorithm == "quickSort")
        quickSort(list, 0, list.size() - 1);
    else if (algorithm == "mergeSort")
        mergeSort(list, 0, list.size() - 1);
    else if (algorithm == "heapSort")
        heapSort(list);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Execution time of " << algorithm << " is " << duration.count() << " seconds" << endl;
}
int main()
{
    srand(time(0));
    vector<int> list = generateRandomList(1000);
    vector<int> listCopy = list;
    measureExecutionTime(list, "bubbleSort");
    measureExecutionTime(list, "selectionSort");
    measureExecutionTime(list, "insertionSort");
    measureExecutionTime(list, "binaryInsertionSort");
    measureExecutionTime(list, "quickSort");
    measureExecutionTime(list, "mergeSort");
    measureExecutionTime(list, "heapSort");
    sort(listCopy.begin(), listCopy.end());
    return 0;
}
