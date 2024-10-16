//SId: 22521240
//Fullname: Le Minh Sang
//Homework - Lab 2 - Question 3

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> canSeePeople(const vector<int>& heights) {
    int n = heights.size();
    vector<int> answer(n, 0);  // Initialize the answer array with zeros
    stack<int> s;               // Stack to hold indices of heights

    for (int i = n - 1; i >= 0; --i) {
        // Count how many people this person can see
        while (!s.empty() && heights[s.top()] < heights[i]) {
            answer[i]++;          // Can see the person at the top of the stack
            s.pop();             // Remove the person from the stack
        }
        if (!s.empty()) {
            answer[i]++;          // Can also see the next taller person
        }
        s.push(i);                // Push this person onto the stack
    }

    return answer;
}

int main() {
    cout<<"SId: 22521240\nFullname: Le Minh Sang\nHomework - Lab 2 - Question 1\n";
    int n;
    cout << "Enter the number of people: ";
    cin >> n;

    vector<int> heights(n);
    cout << "Enter the heights of the people: ";
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    vector<int> result = canSeePeople(heights);
    cout << "Number of people each person can see to their right: ";
    for (int count : result) {
        cout << count << " ";
    }
    cout << endl;

    return 0;
}
