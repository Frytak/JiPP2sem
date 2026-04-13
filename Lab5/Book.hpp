#include <string>

class Book {
private:
    std::string title;
    std::string author;
    double price; 

public:
    Book(std::string title, std::string author, double price);

    std::string get_title();
    std::string get_author();

    double get_price();
    void set_price(double price);
};
