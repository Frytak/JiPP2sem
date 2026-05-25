#include "StudentDB.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <limits>
#include <string>

void print_help() {
    std::cout << "\nDostepne komendy:\n"
              << "  add <id> <imie> <wiek> <ocena>\n"
              << "  list\n"
              << "  find <id>\n"
              << "  update <id> <nowe_imie> <nowy_wiek> <nowa_ocena>\n"
              << "  delete <id>\n"
              << "  exit\n"
              << "> ";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Blad: Nie podano pliku bazy danych.\n"
                  << "Uzycie: " << argv[0] << " <plik_bazy.bin>\n";
        return 1;
    }

    try {
        StudentDB db(argv[1]);
        std::string command;
        
        std::cout << "=== StudentDB ===";
        print_help();

        while (std::cin >> command && command != "exit") {
            try {
                if (command == "add") {
                    uint32_t id; std::string name; uint16_t age; float grade;
                    if (std::cin >> id >> name >> age >> grade) {
                        db.add(id, name, age, grade);
                    } else {
                        throw std::invalid_argument("Nieprawidlowe dane wejsciowe.");
                    }
                } 
                else if (command == "list") {
                    db.list();
                } 
                else if (command == "find") {
                    uint32_t id;
                    if (std::cin >> id) db.find(id);
                    else throw std::invalid_argument("Nieprawidlowe ID.");
                } 
                else if (command == "update") {
                    uint32_t id; std::string name; uint16_t age; float grade;
                    if (std::cin >> id >> name >> age >> grade) {
                        db.update(id, name, age, grade);
                    } else {
                        throw std::invalid_argument("Nieprawidlowe dane wejsciowe.");
                    }
                } 
                else if (command == "delete") {
                    uint32_t id;
                    if (std::cin >> id) db.delete_record(id);
                    else throw std::invalid_argument("Nieprawidlowe ID.");
                } 
                else {
                    std::cout << "Nieznana komenda.\n";
                }
            } 
            catch (const DuplicateRecordException& e) {
                std::cerr << "[BLAD BAZY] " << e.what() << "\n";
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "[BLAD WEJSCIA] " << e.what() << "\n";
            }
            catch (const std::runtime_error& e) {
                std::cerr << "[BLAD SYSTEMU] " << e.what() << "\n";
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            print_help();
        }
    } 
    catch (const DatabaseFormatException& e) {
        std::cerr << "Blad krytyczny formatu bazy: " << e.what() << "\n";
        return 1;
    } 
    catch (const std::exception& e) {
        std::cerr << "Wystapil niespodziewany blad: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
