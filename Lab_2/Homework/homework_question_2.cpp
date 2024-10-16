//SId: 22521240
//Fullname: Le Minh Sang
//Homework - Lab 2 - Question 2

#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Browser
{
public:
    void visit(const string &url)
    {
        // Clear the forward stack since we are visiting a new URL
        while (!forwardStack.empty())
        {
            forwardStack.pop();
        }
        historyStack.push(url);
        cout << "Visited: " << url << endl;
    }

    string back()
    {
        if (historyStack.size() <= 1)
        {
            cout << "No more back history." << endl;
            return "";
        }
        // Move the current URL to the forward stack
        forwardStack.push(historyStack.top());
        historyStack.pop();
        string previousUrl = historyStack.top();
        cout << "Back to: " << previousUrl << endl;
        return previousUrl;
    }

    string forward()
    {
        if (forwardStack.empty())
        {
            cout << "No more forward history." << endl;
            return "";
        }
        string nextUrl = forwardStack.top();
        forwardStack.pop();
        historyStack.push(nextUrl);
        cout << "Forward to: " << nextUrl << endl;
        return nextUrl;
    }

private:
    stack<string> historyStack; // Stack to store history of visited URLs
    stack<string> forwardStack; // Stack to store forward URLs
};

int main()
{
    cout<<"SId: 22521240\nFullname: Le Minh Sang\nHomework - Lab 2 - Question 1\n";
    Browser browser;
    string command, url;

    while (true)
    {
        cout << "Enter command (visit, back, forward, exit): ";
        cin >> command;

        if (command == "visit")
        {
            cout << "Enter URL: ";
            cin >> url;
            browser.visit(url);
        }
        else if (command == "back")
        {
            browser.back();
        }
        else if (command == "forward")
        {
            browser.forward();
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            cout << "Invalid command. Please try again." << endl;
        }
    }

    return 0;
}
