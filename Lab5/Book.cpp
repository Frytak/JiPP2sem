#include "./Book.hpp"
#include <algorithm>

Book::Book(std::string title, std::string author, double price) : title(title), author(author), price(std::max(0., price)) {}

std::string Book::get_title() { return this->title; }
std::string Book::get_author() { return this->author; }

double Book::get_price() { return this->price; }
void Book::set_price(double price) { this->price = std::max(0., price); }
