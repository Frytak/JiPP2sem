#include "Exceptions.hpp"

DatabaseFormatException::DatabaseFormatException(const std::string& msg) 
    : std::runtime_error(msg) {}

DuplicateRecordException::DuplicateRecordException(const std::string& msg) 
    : std::runtime_error(msg) {}
