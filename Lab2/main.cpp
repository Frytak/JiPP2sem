#include <iostream>
#include <string>

#include "./Car.hpp"
#include "./BankAccount.hpp"
#include "./Rectangle.hpp"
#include "./Player.hpp"

int main() {
    // Car class test
    std::cout << "\x1b[1m\x1b[33m=== Car ===\x1b[0m" << std::endl;

    Car car("KIA", 120.);
    car.printInfo();
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    std::cout << std::endl;

    car.accelerate(-12.);
    car.printInfo();
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    std::cout << std::endl;

    car.accelerate(12.);
    car.printInfo();
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    std::cout << std::endl;

    car.accelerate(1000.);
    car.printInfo();
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    std::cout << std::endl;

    car.brake(-10.);
    car.printInfo();
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    std::cout << std::endl;

    car.brake(10.);
    car.printInfo();
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    std::cout << std::endl;

    car.brake(10000.);
    car.printInfo();
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    std::cout << std::endl;

    // BankAccount class test
    std::cout << "\x1b[1m\x1b[33m=== BankAccount ===\x1b[0m" << std::endl;

    BankAccount bank_account("Adam", 1000.);
    BankAccount bank_account2("Iza", 4000.);
    BankAccount bank_account3("Bartek", 2800.);
    bank_account.print();
    bank_account2.print();
    bank_account3.print();
    std::cout << std::endl;

    std::cout << "Id: " << bank_account.getId() << std::endl;
    std::cout << "Balance: " << bank_account.getBalance() << std::endl;
    std::cout << std::endl;

    bank_account.deposit(-285.);
    bank_account.print();
    std::cout << "Balance: " << bank_account.getBalance() << std::endl;
    std::cout << std::endl;

    bank_account.deposit(0.);
    bank_account.print();
    std::cout << "Balance: " << bank_account.getBalance() << std::endl;
    std::cout << std::endl;

    bank_account.deposit(285.);
    bank_account.print();
    std::cout << "Balance: " << bank_account.getBalance() << std::endl;
    std::cout << std::endl;

    std::cout << "Withdrawn: " << bank_account.withdraw(-2000.) << std::endl;
    bank_account.print();
    std::cout << std::endl;

    std::cout << "Withdrawn: " << bank_account.withdraw(100.) << std::endl;
    bank_account.print();
    std::cout << std::endl;

    std::cout << "Withdrawn: " << bank_account.withdraw(2000.) << std::endl;
    bank_account.print();
    std::cout << std::endl;

    // Rectangle class test
    std::cout << "\x1b[1m\x1b[33m=== Rectangle ===\x1b[0m" << std::endl;

    Rectangle rectangle(2, 5);
    Rectangle square = Rectangle::createSquare(2);
    std::cout << "Rectangle" << std::endl;
    std::cout << "\tArea: " << rectangle.area() << std::endl;
    std::cout << "\tPerimeter: " << rectangle.perimeter() << std::endl;
    std::cout << "\tIs square: " << rectangle.isSquare() << std::endl;

    std::cout << std::endl;

    std::cout << "Square" << std::endl;
    std::cout << "\tArea: " << square.area() << std::endl;
    std::cout << "\tPerimeter: " << square.perimeter() << std::endl;
    std::cout << "\tIs square: " << square.isSquare() << std::endl;

    std::cout << std::endl;
    rectangle.scale(2);

    std::cout << "2x scaled rectangle" << std::endl;
    std::cout << "\tArea: " << rectangle.area() << std::endl;
    std::cout << "\tPerimeter: " << rectangle.perimeter() << std::endl;
    std::cout << "\tIs square: " << rectangle.isSquare() << std::endl;

    std::cout << std::endl;

    // Player class test
    std::cout << "\x1b[1m\x1b[33m=== Player ===\x1b[0m" << std::endl;

    Player player("Arctic", 100);
    player.printStatus();
    std::cout << std::endl;

    std::cout << "Taken damage: " << player.takeDamage(-45) << std::endl;
    player.printStatus();
    std::cout << std::endl;

    std::cout << "Taken damage: " << player.takeDamage(45) << std::endl;
    player.printStatus();
    std::cout << std::endl;

    std::cout << "Taken damage: " << player.takeDamage(68) << std::endl;
    player.printStatus();
    std::cout << std::endl;

    std::cout << "Healed: " << player.heal(-45) << std::endl;
    player.printStatus();
    std::cout << std::endl;

    std::cout << "Healed: " << player.heal(15) << std::endl;
    player.printStatus();
    std::cout << std::endl;

    std::cout << "Healed: " << player.heal(1500) << std::endl;
    player.printStatus();
    std::cout << std::endl;

    std::cout << "Leveled up: " << player.levelUp(-45) << std::endl;
    player.printStatus();
    std::cout << std::endl;

    std::cout << "Leveled up: " << player.levelUp(50) << std::endl;
    player.printStatus();
}
