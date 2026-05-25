#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class DatabaseFormatException : public std::runtime_error {
public:
    explicit DatabaseFormatException(const std::string& msg);
};

class DuplicateRecordException : public std::runtime_error {
public:
    explicit DuplicateRecordException(const std::string& msg);
};

#endif
