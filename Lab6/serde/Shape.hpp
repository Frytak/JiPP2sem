#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

class UnknownTypeException : public std::runtime_error {
public:
    explicit UnknownTypeException(const std::string& msg);
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual void serialize(std::ofstream& out) const = 0;
    virtual void deserialize(std::ifstream& in) = 0;
};

class Circle : public Shape {
private:
    double radius;
public:
    explicit Circle(double r = 0.0);
    double area() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;
    
    double get_radius() const;
};

class Rectangle : public Shape {
private:
    double width;
    double height;
public:
    explicit Rectangle(double w = 0.0, double h = 0.0);
    double area() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;
};

class Triangle : public Shape {
private:
    double base;
    double height;
public:
    explicit Triangle(double b = 0.0, double h = 0.0);
    double area() const override;
    void serialize(std::ofstream& out) const override;
    void deserialize(std::ifstream& in) override;
};

std::unique_ptr<Shape> load_shape(std::ifstream& in);

#endif
