#include "Tasks.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

void prepare_test_files() {
    {
        std::ofstream out("valid_doubles.bin", std::ios::binary);
        double values[] = {2.5, 4.5, 5.0};
        for (double v : values) {
            out.write(reinterpret_cast<const char*>(&v), sizeof(double));
        }
    }
    {
        std::ofstream out("invalid_format.bin", std::ios::binary);
        int wrong_format_data = 42; 
        out.write(reinterpret_cast<const char*>(&wrong_format_data), sizeof(int));
    }
}

int main() {
    prepare_test_files();

    std::vector<std::unique_ptr<Task>> task_queue;
    
    task_queue.push_back(std::make_unique<DivideTask>(10.0, 2.0));
    task_queue.push_back(std::make_unique<SqrtTask>(16.0));
    task_queue.push_back(std::make_unique<FileSizeTask>("valid_doubles.bin"));
    task_queue.push_back(std::make_unique<MeanFromBinaryFileTask>("valid_doubles.bin"));
    
    task_queue.push_back(std::make_unique<DivideTask>(5.0, 0.0));
    task_queue.push_back(std::make_unique<SqrtTask>(-4.0));
    task_queue.push_back(std::make_unique<FileSizeTask>("nieistniejacy_plik.bin"));
    task_queue.push_back(std::make_unique<MeanFromBinaryFileTask>("invalid_format.bin"));

    std::cout << "--- URUCHAMIANIE ZADAN ---\n";

    for (const auto& task : task_queue) {
        std::cout << "Zadanie: " << task->name() << "\n";
        try {
            double result = task->run();
            std::cout << " -> Sukces! Wynik: " << result << "\n";
        } 
        catch (const MathException& e) {
            std::cerr << " -> [Math Error]: " << e.what() << "\n";
        } 
        catch (const FileException& e) {
            std::cerr << " -> [File Error]: " << e.what() << "\n";
        } 
        catch (const FormatException& e) {
            std::cerr << " -> [Format Error]: " << e.what() << "\n";
        } 
        catch (const TaskException& e) {
            std::cerr << " -> [General Task Error]: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << " -> [Critical Standard Error]: " << e.what() << "\n";
        }
        std::cout << "--------------------------------------\n";
    }

    std::cout << "Wszystkie zadania z kolejki zostaly przetworzone.\n";
    return 0;
}
