#include <iostream>
#include <string>
#include <stack>
using namespace std;

class BrowserHistory {
private:
    stack<string> backStack;     // Stack lưu trữ lịch sử quay lại
    stack<string> forwardStack;  // Stack lưu trữ lịch sử tiến tới
    string current;              // Trang hiện tại

public:
    // Khởi tạo trình duyệt với trang chủ
    BrowserHistory(string homepage) {
        current = homepage;
    }

    // Thăm URL mới, xóa lịch sử phía trước
    void visit(string url) {
        backStack.push(current);  // Đẩy trang hiện tại vào stack back
        current = url;            // Cập nhật trang hiện tại
        while (!forwardStack.empty()) {
            forwardStack.pop();   // Xóa lịch sử phía trước
        }
    }

    // Di chuyển về sau 'steps' bước, trả về URL hiện tại
    string back(int steps) {
        while (steps > 0 && !backStack.empty()) {
            forwardStack.push(current);  // Đẩy trang hiện tại vào stack forward
            current = backStack.top();   // Chuyển về trang trước đó
            backStack.pop();
            steps--;
        }
        return current;
    }

    // Tiến lên 'steps' bước, trả về URL hiện tại
    string forward(int steps) {
        while (steps > 0 && !forwardStack.empty()) {
            backStack.push(current);     // Đẩy trang hiện tại vào stack back
            current = forwardStack.top(); // Chuyển tới trang phía trước
            forwardStack.pop();
            steps--;
        }
        return current;
    }
};

int main() {
    cout<<"SId: 22521240\nFullname: Le Minh Sang\nHomework - Lab 1";
    string command;
    string homepage;

    // Nhập trang chủ từ bàn phím
    cin >> homepage;
    BrowserHistory browser(homepage); // Tạo trình duyệt với trang chủ

    int n; // Số lượng lệnh
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> command;
        if (command == "visit") {
            string url;
            cin >> url;
            browser.visit(url);
            cout << "null" << endl;  // Lệnh visit trả về null
        } else if (command == "back") {
            int steps;
            cin >> steps;
            cout << browser.back(steps) << endl;  // Lệnh back trả về URL hiện tại
        } else if (command == "forward") {
            int steps;
            cin >> steps;
            cout << browser.forward(steps) << endl;  // Lệnh forward trả về URL hiện tại
        }
    }

    return 0;
}
