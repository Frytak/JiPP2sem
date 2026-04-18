#include <algorithm>
#include <print>
#include <vector>

int main() {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto sum = 0;
    for (auto x : v) {
        sum += x;
    }

    auto odd_count = 0;
    auto even_count = 0;
    std::for_each(v.begin(), v.end(), [&odd_count, &even_count](auto x) {
        if (x % 2 == 0) {
            even_count++;
        } else {
            odd_count++;
        }
    });

    std::print("Suma: {}\n", sum);
    std::print("Parzyste: {}   Nieparzyste: {}\n", even_count, odd_count);
}
