#include "./Rectangle.hpp"
#include <cstdlib>

Rectangle::Rectangle(double width, double height) : width(std::abs(width)), height(std::abs(height)) {}

double Rectangle::area() const {
    return this->width * this->height;
}

double Rectangle::perimeter() const {
    return (this->width * 2) + (this->height * 2);
}

bool Rectangle::isSquare() const {
    return this->width == this->height;
}

void Rectangle::scale(double amount) {
    amount = std::abs(amount);
    this->width *= amount;
    this->height *= amount;
}

Rectangle Rectangle::createSquare(double side) {
    return Rectangle(side, side);
}
