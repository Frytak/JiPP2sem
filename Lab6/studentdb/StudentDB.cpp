#include "StudentDB.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>

StudentDB::StudentDB(const std::string& db_name) : filename(db_name) {
    validate_database();
}

void StudentDB::validate_database() {
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::ofstream out(filename, std::ios::binary);
        if (!out) {
            throw std::runtime_error("Nie mozna utworzyc pliku bazy danych: " + filename);
        }
        out.write(reinterpret_cast<const char*>(&MAGIC_HEADER), sizeof(MAGIC_HEADER));
        if (!out.good()) {
            throw std::runtime_error("Blad zapisu naglowka do nowego pliku.");
        }
        return;
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    
    if (size < static_cast<std::streamsize>(sizeof(MAGIC_HEADER))) {
        throw DatabaseFormatException("Plik uszkodzony: zbyt maly rozmiar na naglowek.");
    }

    file.seekg(0, std::ios::beg);
    uint32_t file_magic;
    if (!file.read(reinterpret_cast<char*>(&file_magic), sizeof(file_magic))) {
        throw std::runtime_error("Blad odczytu naglowka pliku.");
    }
    
    if (file_magic != MAGIC_HEADER) {
        throw DatabaseFormatException("Niepoprawny naglowek. To nie jest plik StudentDB.");
    }

    std::streamsize data_size = size - static_cast<std::streamsize>(sizeof(MAGIC_HEADER));
    if (data_size % sizeof(StudentRecord) != 0) {
        throw DatabaseFormatException("Plik uszkodzony: rozmiar nie jest wielokrotnoscia rekordu.");
    }
}

std::streampos StudentDB::find_position(uint32_t id, StudentRecord& out_record) const {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Blad otwarcia pliku do odczytu.");

    file.seekg(sizeof(MAGIC_HEADER), std::ios::beg);

    while (file.read(reinterpret_cast<char*>(&out_record), sizeof(StudentRecord))) {
        if (out_record.id == id) {
            return file.tellg() - static_cast<std::streamoff>(sizeof(StudentRecord));
        }
    }
    return -1;
}

void StudentDB::add(uint32_t id, const std::string& name, uint16_t age, float grade) {
    StudentRecord rec;
    std::streampos pos = find_position(id, rec);
    
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) throw std::runtime_error("Blad otwarcia pliku do zapisu.");

    if (pos != std::streampos(-1)) {
        if (rec.active) {
            throw DuplicateRecordException("Rekord o ID " + std::to_string(id) + " juz istnieje!");
        }
        file.seekp(pos);
    } else {
        file.seekp(0, std::ios::end);
    }

    rec.id = id;
    std::memset(rec.name, 0, sizeof(rec.name));
    std::strncpy(rec.name, name.c_str(), sizeof(rec.name) - 1);
    rec.age = age;
    rec.grade = grade;
    rec.active = true;

    if (!file.write(reinterpret_cast<const char*>(&rec), sizeof(StudentRecord))) {
        throw std::runtime_error("Krytyczny blad zapisu danych na dysk.");
    }
    std::cout << "Dodano studenta.\n";
}

void StudentDB::list() const {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Blad otwarcia pliku do odczytu.");

    file.seekg(sizeof(MAGIC_HEADER), std::ios::beg);
    
    StudentRecord rec;
    bool any_found = false;
    
    while (file.read(reinterpret_cast<char*>(&rec), sizeof(StudentRecord))) {
        if (rec.active) {
            std::cout << "ID: " << rec.id << " | Imie: " << rec.name 
                      << " | Wiek: " << rec.age << " | Ocena: " << rec.grade << "\n";
            any_found = true;
        }
    }
    if (!any_found) std::cout << "Baza jest pusta.\n";
}

void StudentDB::find(uint32_t id) const {
    StudentRecord rec;
    if (find_position(id, rec) != std::streampos(-1) && rec.active) {
        std::cout << "Znaleziono - ID: " << rec.id << " | Imie: " << rec.name 
                  << " | Wiek: " << rec.age << " | Ocena: " << rec.grade << "\n";
    } else {
        std::cout << "Nie znaleziono studenta o ID: " << id << "\n";
    }
}

void StudentDB::update(uint32_t id, const std::string& name, uint16_t age, float grade) {
    StudentRecord rec;
    std::streampos pos = find_position(id, rec);
    
    if (pos != std::streampos(-1) && rec.active) {
        std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
        if (!file) throw std::runtime_error("Blad otwarcia pliku do aktualizacji.");

        file.seekp(pos);
        
        std::memset(rec.name, 0, sizeof(rec.name));
        std::strncpy(rec.name, name.c_str(), sizeof(rec.name) - 1);
        rec.age = age;
        rec.grade = grade;
        
        if (!file.write(reinterpret_cast<const char*>(&rec), sizeof(StudentRecord))) {
            throw std::runtime_error("Blad modyfikacji rekordu na dysku.");
        }
        std::cout << "Zaktualizowano rekord.\n";
    } else {
        std::cout << "Nie znaleziono studenta o ID: " << id << "\n";
    }
}

void StudentDB::delete_record(uint32_t id) {
    StudentRecord rec;
    std::streampos pos = find_position(id, rec);
    
    if (pos != std::streampos(-1) && rec.active) {
        std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
        if (!file) throw std::runtime_error("Blad otwarcia pliku do usuniecia.");

        file.seekp(pos);
        rec.active = false;
        
        if (!file.write(reinterpret_cast<const char*>(&rec), sizeof(StudentRecord))) {
            throw std::runtime_error("Blad oznaczania rekordu jako usuniety.");
        }
        std::cout << "Usunieto studenta.\n";
    } else {
        std::cout << "Nie znaleziono studenta o ID: " << id << "\n";
    }
}
