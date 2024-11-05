#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cmath>

struct Point {
    double x, y;
};

double distance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void knnSearch(const std::vector<Point> &dataset, const Point &query, int k, int start, int end, std::vector<Point> &results, std::mutex &m) {
    std::vector<std::pair<double, Point>> distances;
    for (int i = start; i < end; ++i) {
        double dist = distance(dataset[i], query);
        distances.emplace_back(dist, dataset[i]);
    }

    std::sort(distances.begin(), distances.end());
    for (int i = 0; i < k && i < distances.size(); ++i) {
        std::lock_guard<std::mutex> lock(m);
        results.push_back(distances[i].second);
    }
}

int main() {
    std::vector<Point> dataset = { {1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10} };
    Point query = {5, 5};
    int k = 3;
    int numThreads = 2;
    std::vector<std::thread> threads;
    std::vector<Point> results;
    std::mutex m;

    int chunkSize = dataset.size() / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? dataset.size() : (i + 1) * chunkSize;
        threads.emplace_back(knnSearch, std::ref(dataset), query, k, start, end, std::ref(results), std::ref(m));
    }

    for (auto &t : threads) {
        t.join();
    }

    std::cout << "K Nearest Neighbors:\n";
    for (const auto &p : results) {
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
