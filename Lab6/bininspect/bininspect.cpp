#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

class InvalidArgs: public std::exception {
private:
    std::string msg;

public:
    InvalidArgs(const char *msg) : msg(msg) {};

    const char* what() const noexcept override {
        return this->msg.c_str();
    }
};

#define ARG_COUNT 1

int main(int argc, char* argv[]) {
    try {
        if (argc != ARG_COUNT + 1) {
            throw InvalidArgs("Niepoprawna ilość argumentów. Oczekiwano jeden argument - ścieżka do pliku binarnego.");
        }

        std::ifstream bin_file;
        bin_file.open(argv[1], std::ios::binary);

        // Get file size
        bin_file.ignore(std::numeric_limits<std::streamsize>::max());
        std::streamsize size = bin_file.gcount() - 1;
        bin_file.clear();
        bin_file.seekg(0, std::ios_base::beg);

        std::vector<unsigned char> bin(std::istreambuf_iterator<char>(bin_file), {});

        std::cout << std::hex;
        for (int i = 0; i < size/8; i++) {
            for (int j = i*8; j < i; j++) {
                std::cout << bin[j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    } catch(InvalidArgs &err) {
        std::cerr << err.what() << std::endl;
    }
}
