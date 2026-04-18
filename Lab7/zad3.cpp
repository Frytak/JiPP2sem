#include <iostream>
#include <optional>
#include <vector>

std::optional<int> find_even(const std::vector<int> &v) {
    for (int x : v) {
        if (x % 2 == 0) {
            return x;
        }
    }

    return std::nullopt;
}

int main() {
    auto v = std::vector<int>{1, 3, 5, 7, 8, 9};
    auto res = find_even(v);

    if (res) {
        std::cout << *res;
    }
}
