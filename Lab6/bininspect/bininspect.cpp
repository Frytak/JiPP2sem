#include "BinaryInspector.hpp"
#include <iostream>
#include <string>

void printUsage(const char* progName) {
    std::cerr << "Uzycie: " << progName << " <plik_binarny> [--offset N --type u16|u32|u64]\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string filename = argv[1];
    
    bool hasOffset = false;
    std::size_t offset = 0;
    DataType typeToRead = DataType::U32;

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--offset" && i + 1 < argc) {
            try {
                offset = std::stoull(argv[++i]);
                hasOffset = true;
            } catch (const std::exception&) {
                std::cerr << "Blad: Niepoprawna wartosc dla opcji --offset\n";
                return 1;
            }
        } 
        else if (arg == "--type" && i + 1 < argc) {
            std::string t = argv[++i];
            if (t == "u16") typeToRead = DataType::U16;
            else if (t == "u32") typeToRead = DataType::U32;
            else if (t == "u64") typeToRead = DataType::U64;
            else {
                std::cerr << "Blad: Nieznany typ '" << t << "'. Dozwolone: u16, u32, u64\n";
                return 1;
            }
        } 
        else {
            std::cerr << "Blad: Nieznany lub niekompletny argument: " << arg << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }

    try {
        BinaryInspector inspector(filename);
        
        inspector.printFileSize();
        std::cout << "\n";
        inspector.printHexAndAsciiDump(64);
        std::cout << "\n";
        inspector.printByteFrequencies();
        std::cout << "\n";

        if (hasOffset) {
            inspector.printValueAt(offset, typeToRead);
        }

    } 
    catch (const BinaryRangeException& e) {
        std::cerr << "\n[WYJATEK LOGICZNY] " << e.what() << "\n";
        return 1;
    }
    catch (const FileOpenException& e) {
        std::cerr << "\n[WYJATEK I/O] " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "\n[NIEOCZEKIWANY WYJATEK] " << e.what() << "\n";
        return 1;
    }

    return 0;
}
