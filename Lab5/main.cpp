#include <cstdio>
#include "./Order.hpp"

int main() {
    Order order{};

    Book chlopi("Chłopi", "Władysław Reymont", 24.99);
    Book g1984("1984", "George Orwell", 19.84);
    Book inny_swiat("Inny Świat", "Gustaw Herling-Grudziński", 0);

    order += g1984;
    order += chlopi;
    order += chlopi;
    order += chlopi;
    order += inny_swiat;

    std::printf("Cena zamówienia: %.2lfzł\n", order.calculate_total_price());
    std::printf("Cena zamówienia z dostawą: %.2lfzł\n", order.calculate_total_price(20));
}
