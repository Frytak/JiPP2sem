#include <cstdlib>
#include <memory>
#include <print>
#include <unistd.h>

int *raw() {
    int *x = new int(42);
    return x;
}

std::unique_ptr<int> smart() {
    std::unique_ptr<int> x = std::make_unique<int>(42);
    return x;
}

int main() {
    int iters = 10000000;

    for (int i = 0; i < iters; i++) {
        smart();
    }

    std::print("Smart done, no leaks\n");
    sleep(4);

    for (int i = 0; i < iters; i++) {
        raw();
    }

    std::print("Raw done, leaks D:\n");
    sleep(4);
}
