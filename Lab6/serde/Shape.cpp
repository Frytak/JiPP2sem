#include "Shape.hpp"

UnknownTypeException::UnknownTypeException(const std::string& msg) 
    : std::runtime_error(msg) {}

Circle::Circle(double r) : radius(r) {}

double Circle::area() const { 
    return 3.141592653589793 * radius * radius; 
}

void Circle::serialize(std::ofstream& out) const {
    char type_id = 'C';
    out.write(&type_id, sizeof(type_id));
    out.write(reinterpret_cast<const char*>(&radius), sizeof(radius));
}

void Circle::deserialize(std::ifstream& in) {
    if (!in.read(reinterpret_cast<char*>(&radius), sizeof(radius))) {
        throw std::runtime_error("Blad odczytu danych: uszkodzony rekord typu Circle.");
    }
}

double Circle::get_radius() const { 
    return radius; 
}

Rectangle::Rectangle(double w, double h) : width(w), height(h) {}

double Rectangle::area() const { 
    return width * height; 
}

void Rectangle::serialize(std::ofstream& out) const {
    char type_id = 'R';
    out.write(&type_id, sizeof(type_id));
    out.write(reinterpret_cast<const char*>(&width), sizeof(width));
    out.write(reinterpret_cast<const char*>(&height), sizeof(height));
}

void Rectangle::deserialize(std::ifstream& in) {
    if (!in.read(reinterpret_cast<char*>(&width), sizeof(width)) ||
        !in.read(reinterpret_cast<char*>(&height), sizeof(height))) {
        throw std::runtime_error("Blad odczytu danych: uszkodzony rekord typu Rectangle.");
    }
}

Triangle::Triangle(double b, double h) : base(b), height(h) {}

double Triangle::area() const { 
    return 0.5 * base * height; 
}

void Triangle::serialize(std::ofstream& out) const {
    char type_id = 'T';
    out.write(&type_id, sizeof(type_id));
    out.write(reinterpret_cast<const char*>(&base), sizeof(base));
    out.write(reinterpret_cast<const char*>(&height), sizeof(height));
}

void Triangle::deserialize(std::ifstream& in) {
    if (!in.read(reinterpret_cast<char*>(&base), sizeof(base)) ||
        !in.read(reinterpret_cast<char*>(&height), sizeof(height))) {
        throw std::runtime_error("Blad odczytu danych: uszkodzony rekord typu Triangle.");
    }
}

std::unique_ptr<Shape> load_shape(std::ifstream& in) {
    char type_id;
    if (!in.read(&type_id, sizeof(type_id))) {
        return nullptr;
    }

    std::unique_ptr<Shape> shape;
    switch (type_id) {
        case 'C': shape = std::make_unique<Circle>(); break;
        case 'R': shape = std::make_unique<Rectangle>(); break;
        case 'T': shape = std::make_unique<Triangle>(); break;
        default: 
            throw UnknownTypeException("Nieznany identyfikator typu w pliku: '" + std::string(1, type_id) + "'");
    }
    
    shape->deserialize(in);
    return shape;
}
