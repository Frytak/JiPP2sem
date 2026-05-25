#include <iostream>
#include <ostream>
#include <string>
#include <variant>

struct Visitor {
    void operator() (const int &num) { std::cout << "int = " << num; }
    void operator() (const std::string &str) { std::cout << "std::string = " << str; }
};

int main() {
    std::variant<int, std::string> int_or_str = "Następnie będzie `int`";

    std::visit(Visitor {}, int_or_str);
    std::cout << std::endl;

    int_or_str = 67;

    std::visit(Visitor {}, int_or_str);
    std::cout << std::endl;
}
