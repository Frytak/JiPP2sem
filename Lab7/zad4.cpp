#include <iostream>
#include <ostream>
#include <utility>

struct Point {
    int x, y;
};

std::pair<int, int> point_as_pair(Point p) {
    return std::make_pair(p.x, p.y);
}

int main() {
    Point p1{1, 2};
    Point p2{3, 4};

    auto [x1, y1] = p1;
    auto [x2, y2] = point_as_pair(p2);

    std::cout << "p1: (" << x1 << ", " << y1 << ")\n";
    std::cout << "p2: (" << x2 << ", " << y2 << ")" << std::endl;
}
