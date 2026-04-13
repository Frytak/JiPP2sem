#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include "./Book.hpp"

typedef std::pair<Book, std::uint32_t> BookWithAmount;

class Order {
private:
    std::map<std::string, BookWithAmount> shopping_cart;

public:
    Order();

    Order& operator+=(Book &rhs);
    double calculate_total_price();
    double calculate_total_price(double delivery_price);
};
