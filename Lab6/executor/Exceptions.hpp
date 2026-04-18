#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class TaskException : public std::runtime_error {
public:
    explicit TaskException(const std::string& msg) : std::runtime_error(msg) {}
};

class MathException : public TaskException {
public:
    explicit MathException(const std::string& msg) : TaskException(msg) {}
};

class FileException : public TaskException {
public:
    explicit FileException(const std::string& msg) : TaskException(msg) {}
};

class FormatException : public TaskException {
public:
    explicit FormatException(const std::string& msg) : TaskException(msg) {}
};

#endif
