#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include "./Car.hpp"

Car::Car(std::string brand, double maxSpeed) : brand(brand), speed(0), maxSpeed(std::max(maxSpeed, 0.)) { }

void Car::accelerate(double amount) {
    this->speed += std::max(amount, 0.);
    this->speed = std::min(this->speed, this->maxSpeed);
}

void Car::brake(double amount) {
    this->speed -= std::max(amount, 0.);
    this->speed = std::max(this->speed, 0.);
}

double Car::getSpeed() const {
    return this->speed;
}

void Car::printInfo() const {
    std::cout << "Car { brand: \"" << this->brand << "\", speed: " << this->speed << ", maxSpeed: " << this->maxSpeed << " }" << std::endl;
}
