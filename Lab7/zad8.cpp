#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> describe(int x) {
    if (x < 0) { return std::nullopt; }

    if (x %= 2) {
        return "even";
    } else {
        return "odd";
    }
}

int main() {
    auto describe_or_idk = [](auto x) { return describe(x).value_or("idk what to say man"); };

    std::cout << "5: " << describe_or_idk(5) << std::endl;
    std::cout << "2: " << describe_or_idk(2) << std::endl;
    std::cout << "-2: " << describe_or_idk(-2) << std::endl;
}
