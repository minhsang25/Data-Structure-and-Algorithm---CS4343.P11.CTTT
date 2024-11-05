#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
    double x, y;
};

double distance(const Point &p1, const Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool compareX(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

bool compareY(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

double closestPairUtil(std::vector<Point> &px, std::vector<Point> &py) {
    if (px.size() <= 3) {
        double minDist = std::numeric_limits<double>::max();
        for (size_t i = 0; i < px.size(); i++) {
            for (size_t j = i + 1; j < px.size(); j++) {
                minDist = std::min(minDist, distance(px[i], px[j]));
            }
        }
        return minDist;
    }

    size_t mid = px.size() / 2;
    Point midPoint = px[mid];

    std::vector<Point> pyl, pyr;
    for (const auto &p : py) {
        if (p.x <= midPoint.x) pyl.push_back(p);
        else pyr.push_back(p);
    }

    double dl = closestPairUtil(px, pyl);
    double dr = closestPairUtil(px, pyr);
    double d = std::min(dl, dr);

    std::vector<Point> strip;
    for (const auto &p : py) {
        if (fabs(p.x - midPoint.x) < d) strip.push_back(p);
    }

    for (size_t i = 0; i < strip.size(); i++) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++) {
            d = std::min(d, distance(strip[i], strip[j]));
        }
    }

    return d;
}

double closestPair(std::vector<Point> &points) {
    std::vector<Point> px = points;
    std::vector<Point> py = points;
    std::sort(px.begin(), px.end(), compareX);
    std::sort(py.begin(), py.end(), compareY);
    return closestPairUtil(px, py);
}

int main() {
    std::vector<Point> points = { {0, 0}, {1, 1}, {2, 2}, {3, 3}, {5, 5}, {2, 1} };
    std::cout << "The closest distance is: " << closestPair(points) << "\n";
    return 0;
}
