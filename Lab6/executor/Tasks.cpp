#include "Tasks.hpp"
#include "Exceptions.hpp"
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iostream>

DivideTask::DivideTask(double a, double b) : a(a), b(b) {}

std::string DivideTask::name() const {
    return "DivideTask (" + std::to_string(a) + " / " + std::to_string(b) + ")";
}

double DivideTask::run() const {
    if (b == 0.0) {
        throw MathException("Dzielenie przez zero.");
    }
    return a / b;
}

SqrtTask::SqrtTask(double x) : x(x) {}

std::string SqrtTask::name() const {
    return "SqrtTask (" + std::to_string(x) + ")";
}

double SqrtTask::run() const {
    if (x < 0.0) {
        throw MathException("Pierwiastek kwadratowy z liczby ujemnej.");
    }
    return std::sqrt(x);
}

FileSizeTask::FileSizeTask(const std::string& path) : path(path) {}

std::string FileSizeTask::name() const {
    return "FileSizeTask (" + path + ")";
}

double FileSizeTask::run() const {
    std::error_code ec;
    auto size = std::filesystem::file_size(path, ec);
    if (ec) {
        throw FileException("Nie mozna pobrac rozmiaru pliku: " + path + " (Powod: " + ec.message() + ")");
    }
    return static_cast<double>(size);
}

MeanFromBinaryFileTask::MeanFromBinaryFileTask(const std::string& path) : path(path) {}

std::string MeanFromBinaryFileTask::name() const {
    return "MeanFromBinaryFileTask (" + path + ")";
}

double MeanFromBinaryFileTask::run() const {
    try {
        std::ifstream file(path, std::ios::binary | std::ios::ate);
        if (!file) {
            throw FileException("Nie mozna otworzyc pliku binarnego: " + path);
        }

        std::streamsize size = file.tellg();
        if (size == 0) {
            throw FormatException("Plik jest pusty. Brak danych do wyliczenia sredniej.");
        }
        if (size % sizeof(double) != 0) {
            throw FormatException("Rozmiar pliku nie jest wielokrotnoscia rozmiaru typu double.");
        }

        file.seekg(0, std::ios::beg);
        
        double sum = 0.0;
        double value = 0.0;
        size_t elements_count = static_cast<size_t>(size) / sizeof(double);

        for (size_t i = 0; i < elements_count; ++i) {
            if (!file.read(reinterpret_cast<char*>(&value), sizeof(double))) {
                throw FileException("Niespodziewany blad podczas czytania double z pliku.");
            }
            sum += value;
        }

        return sum / static_cast<double>(elements_count);

    } catch (const TaskException& e) {
        std::cerr << "[LOG WEWNETRZNY TASKU] Blad przetwarzania pliku: " << e.what() << "\n";
        throw; 
    }
}
