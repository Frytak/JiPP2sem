#include <algorithm>
#include <iostream>
#include <string>
#include "./BankAccount.hpp"

int BankAccount::nextId = 0;

BankAccount::BankAccount(std::string owner, double balance) : owner(owner), balance(std::max(balance, 0.)), id(nextId++) { }

void BankAccount::deposit(double amount) {
    this->balance += std::max(amount, 0.);
}

double BankAccount::withdraw(double amount) {
    double withdrawn = std::max(std::min(this->balance, amount), 0.);
    this->balance -= withdrawn;
    return withdrawn;
}

double BankAccount::getBalance() const {
    return this->balance;
}

int BankAccount::getId() const {
    return this->id;
}

void BankAccount::print() const {
    std::cout << "BankAccount { id: " << this->id << ", owner: \"" << this->owner << "\", balance: " << this->balance << " }" << std::endl;
}
