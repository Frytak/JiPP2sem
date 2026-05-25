#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int counter = 0;

    std::for_each(vec.begin(), vec.end(), [&counter](auto) {
        counter++;
        std::cout << "Counter in reference lambda: " << counter << std::endl;
    });

    // Oryginalna wartość się nie zmienia bo wartość `counter` została skopiowana
    std::for_each(vec.begin(), vec.end(), [=](auto) mutable {
        counter++;
        std::cout << "Counter in copy lambda: " << counter << std::endl;
    });

    std::cout << "\nCounter: " << counter << std::endl;
}
