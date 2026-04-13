#include "./Order.hpp"
#include <cstdint>
#include <utility>

Order::Order() : shopping_cart(std::map<std::string, BookWithAmount>()) {}

Order& Order::operator+=(Book &rhs) {
    std::string key = rhs.get_title() + rhs.get_author();
    auto book = this->shopping_cart.find(key);

    std::uint32_t amount = 1;
    if (book != this->shopping_cart.end()) {
        amount = (book->second.second + 1);
    }

    this->shopping_cart.insert_or_assign(key, std::pair(rhs, amount));

    return *this;
}

double Order::calculate_total_price() {
    double total_price = 0;

    for (auto book_with_amount = this->shopping_cart.begin(); book_with_amount != this->shopping_cart.end(); book_with_amount++) {
        std::uint32_t amount = book_with_amount->second.second;
        double book_price = book_with_amount->second.first.get_price();
        total_price += (amount * book_price);
    }

    return total_price;
}

double Order::calculate_total_price(double delivery_price) {
    return this->calculate_total_price() + delivery_price;
}
