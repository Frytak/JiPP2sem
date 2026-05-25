#ifndef STUDENT_RECORD_HPP
#define STUDENT_RECORD_HPP

#include <cstdint>

#pragma pack(push, 1)
struct StudentRecord {
    uint32_t id;
    char name[32];
    uint16_t age;
    float grade;
    bool active;
};
#pragma pack(pop)

#endif
