#include "BinaryInspector.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <array>
#include <vector>
#include <cctype>

BinaryRangeException::BinaryRangeException(const std::string& msg) 
    : std::runtime_error(msg) {}

FileOpenException::FileOpenException(const std::string& msg) 
    : std::runtime_error(msg) {}

BinaryInspector::BinaryInspector(const std::string& path) : filename(path), fileSize(0) {
    determineFileSize();
}

void BinaryInspector::determineFileSize() {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        throw FileOpenException("Nie mozna otworzyc pliku: " + filename);
    }
    fileSize = static_cast<std::size_t>(file.tellg());
}

void BinaryInspector::printFileSize() const {
    std::cout << "[INFO] Rozmiar pliku: " << fileSize << " bajtow.\n";
}

void BinaryInspector::printHexAndAsciiDump(std::size_t limit) const {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw FileOpenException("Nie mozna otworzyc pliku do zrzutu.");

    std::size_t bytesToRead = std::min(fileSize, limit);
    std::vector<char> buffer(bytesToRead);
    
    if (bytesToRead > 0) {
        file.read(buffer.data(), bytesToRead);
    }

    std::cout << "[DUMP] Pierwsze " << bytesToRead << " bajtow:\n";
    
    for (std::size_t i = 0; i < bytesToRead; i += 16) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << i << "  ";

        std::size_t rowEnd = std::min(i + 16, bytesToRead);
        for (std::size_t j = i; j < i + 16; ++j) {
            if (j < rowEnd) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') 
                          << static_cast<unsigned int>(static_cast<unsigned char>(buffer[j])) << " ";
            } else {
                std::cout << "   ";
            }
        }

        std::cout << " |";

        for (std::size_t j = i; j < rowEnd; ++j) {
            unsigned char c = static_cast<unsigned char>(buffer[j]);
            if (std::isprint(c)) {
                std::cout << c;
            } else {
                std::cout << '.';
            }
        }
        std::cout << "|\n";
    }
    std::cout << std::dec << std::setfill(' '); 
}

void BinaryInspector::printByteFrequencies() const {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw FileOpenException("Nie mozna otworzyc pliku do analizy frekwencji.");

    std::array<std::size_t, 256> frequencies = {0};
    std::vector<char> buffer(4096);
    
    while (file.read(buffer.data(), buffer.size()) || file.gcount() > 0) {
        std::streamsize bytesRead = file.gcount();
        for (std::streamsize i = 0; i < bytesRead; ++i) {
            unsigned char c = static_cast<unsigned char>(buffer[i]);
            frequencies[c]++;
        }
    }

    std::cout << "[FREQ] Czestotliwosc bajtow (tylko wystepujace):\n";
    for (std::size_t i = 0; i < 256; ++i) {
        if (frequencies[i] > 0) {
            std::cout << "  0x" << std::hex << std::setw(2) << std::setfill('0') << i 
                      << std::dec << std::setfill(' ') << " : " << frequencies[i] << "\n";
        }
    }
}

void BinaryInspector::printValueAt(std::size_t offset, DataType type) const {
    std::size_t bytesNeeded = 0;
    std::string typeName;

    switch (type) {
        case DataType::U16: bytesNeeded = sizeof(uint16_t); typeName = "uint16_t"; break;
        case DataType::U32: bytesNeeded = sizeof(uint32_t); typeName = "uint32_t"; break;
        case DataType::U64: bytesNeeded = sizeof(uint64_t); typeName = "uint64_t"; break;
    }

    if (offset + bytesNeeded > fileSize) {
        throw BinaryRangeException("Offset " + std::to_string(offset) + 
                                   " wychodzi poza rozmiar pliku (rozmiar: " + std::to_string(fileSize) + ").");
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file) throw FileOpenException("Nie mozna otworzyc pliku do odczytu wartosci.");

    file.seekg(offset, std::ios::beg);

    std::cout << "[DATA] Odczyt " << typeName << " z offsetu " << offset << ":\n";
    
    if (type == DataType::U16) {
        uint16_t val;
        file.read(reinterpret_cast<char*>(&val), bytesNeeded);
        std::cout << "  Wartosc: " << val << " (0x" << std::hex << val << std::dec << ")\n";
    } 
    else if (type == DataType::U32) {
        uint32_t val;
        file.read(reinterpret_cast<char*>(&val), bytesNeeded);
        std::cout << "  Wartosc: " << val << " (0x" << std::hex << val << std::dec << ")\n";
    } 
    else if (type == DataType::U64) {
        uint64_t val;
        file.read(reinterpret_cast<char*>(&val), bytesNeeded);
        std::cout << "  Wartosc: " << val << " (0x" << std::hex << val << std::dec << ")\n";
    }
}
