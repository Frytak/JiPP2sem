#include "Shape.hpp"
#include <iostream>
#include <vector>
#include <typeinfo>

int main() {
    const std::string filename = "shapes.bin";

    std::vector<std::unique_ptr<Shape>> shapes_to_save;
    shapes_to_save.push_back(std::make_unique<Circle>(5.0));
    shapes_to_save.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes_to_save.push_back(std::make_unique<Triangle>(10.0, 3.0));

    {
        std::ofstream out(filename, std::ios::binary);
        if (!out) {
            std::cerr << "Blad krytyczny: Nie mozna otworzyc pliku '" << filename << "' do zapisu.\n";
            return 1;
        }

        for (const auto& shape : shapes_to_save) {
            shape->serialize(out);
        }

        if (!out.good()) {
            std::cerr << "Blad zapisu: Wystapil problem z dyskiem podczas zrzucania danych.\n";
            return 1;
        }
        std::cout << "Zapisano ksztalty do pliku.\n";
    }

    std::vector<std::unique_ptr<Shape>> loaded_shapes;
    {
        std::ifstream in(filename, std::ios::binary);
        if (!in) {
            std::cerr << "Blad krytyczny: Nie mozna otworzyc pliku '" << filename << "' do odczytu.\n";
            return 1;
        }

        try {
            while (in.peek() != EOF) {
                auto shape = load_shape(in);
                if (shape) {
                    loaded_shapes.push_back(std::move(shape));
                }
            }
            std::cout << "Pomyslnie odczytano wszystkie ksztalty.\n\n";
        } 
        catch (const UnknownTypeException& e) {
            std::cerr << "Blad formatu pliku (Zly typ): " << e.what() << "\n";
            return 1;
        } 
        catch (const std::exception& e) {
            std::cerr << "Blad I/O (Uszkodzone dane): " << e.what() << "\n";
            return 1;
        }
    }

    for (const auto& shape : loaded_shapes) {
        std::cout << "Typ wg RTTI: " << typeid(*shape).name() << "\n"
                  << "Pole powierzchni: " << shape->area() << "\n";

        if (Circle* circle = dynamic_cast<Circle*>(shape.get())) {
            std::cout << " -> (dynamic_cast zadzialal) Pobrany promien: " << circle->get_radius() << "\n";
        }
        std::cout << "-----------------------------------\n";
    }

    return 0;
}
