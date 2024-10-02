#include <iostream>
#include <string>
using namespace std;

class AuthenticationManager {
private:
    struct Token {
        string tokenId;
        int expiryTime;
    };

    Token tokens[100];  // Mảng lưu trữ token (giới hạn ở 100 token)
    int tokenCount;     // Đếm số lượng token hiện tại
    int timeToLive;     // Thời gian sống của token

public:
    // Constructor: khởi tạo với thời gian sống của token
    AuthenticationManager(int ttl) {
        timeToLive = ttl;
        tokenCount = 0;  // Khởi tạo số lượng token là 0
    }

    // Tạo token với ID và thời gian hiện tại
    void generate(string tokenId, int currentTime) {
        tokens[tokenCount].tokenId = tokenId;
        tokens[tokenCount].expiryTime = currentTime + timeToLive;  // Đặt thời gian hết hạn
        tokenCount++;
    }

    // Gia hạn token nếu chưa hết hạn
    void renew(string tokenId, int currentTime) {
        for (int i = 0; i < tokenCount; ++i) {
            if (tokens[i].tokenId == tokenId && tokens[i].expiryTime > currentTime) {
                tokens[i].expiryTime = currentTime + timeToLive;  // Gia hạn token
                return;
            }
        }
    }

    // Đếm số token chưa hết hạn tại thời điểm hiện tại
    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        for (int i = 0; i < tokenCount; ++i) {
            if (tokens[i].expiryTime > currentTime) {
                count++;  // Đếm số token chưa hết hạn
            }
        }
        return count;
    }
};

int main() {
    int timeToLive;
    cout << "Nhập thời gian sống của token (TTL): ";
    cin >> timeToLive;

    AuthenticationManager manager(timeToLive);

    int n; // Số lượng lệnh
    cout << "Nhập số lượng lệnh: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;

        if (command == "generate") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime;
            manager.generate(tokenId, currentTime);
        } else if (command == "renew") {
            string tokenId;
            int currentTime;
            cin >> tokenId >> currentTime;
            manager.renew(tokenId, currentTime);
        } else if (command == "count") {
            int currentTime;
            cin >> currentTime;
            cout << manager.countUnexpiredTokens(currentTime) << endl;  // In ra số token chưa hết hạn
        }
    }

    return 0;
}
