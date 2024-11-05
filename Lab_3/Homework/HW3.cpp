#include <iostream>
#include <thread>
#include <chrono>

void performSearch(int retry) {
    // Simulated search operation
    if (retry < 3) { // Simulate failures
        throw std::runtime_error("Search failed");
    }
    std::cout << "Search successful!\n";
}

void exponentialBackoff(int maxRetries) {
    for (int retry = 0; retry < maxRetries; ++retry) {
        try {
            performSearch(retry);
            break; // Exit on success
        } catch (const std::runtime_error &) {
            int waitTime = std::pow(2, retry); // Exponential backoff
            std::cout << "Retrying in " << waitTime << " seconds...\n";
            std::this_thread::sleep_for(std::chrono::seconds(waitTime));
        }
    }
}

int main() {
    exponentialBackoff(5);
    return 0;
}
