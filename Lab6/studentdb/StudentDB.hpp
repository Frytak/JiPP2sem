#ifndef STUDENT_DB_HPP
#define STUDENT_DB_HPP

#include "StudentRecord.hpp"
#include <string>

class StudentDB {
private:
    std::string filename;
    static constexpr uint32_t MAGIC_HEADER = 0x53444231;

    void validate_database();
    std::streampos find_position(uint32_t id, StudentRecord& out_record) const;

public:
    explicit StudentDB(const std::string& db_name);
    
    void add(uint32_t id, const std::string& name, uint16_t age, float grade);
    void list() const;
    void find(uint32_t id) const;
    void update(uint32_t id, const std::string& name, uint16_t age, float grade);
    void delete_record(uint32_t id);
};

#endif
