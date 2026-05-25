#ifndef BINARY_INSPECTOR_HPP
#define BINARY_INSPECTOR_HPP

#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstddef>

class BinaryRangeException : public std::runtime_error {
public:
    explicit BinaryRangeException(const std::string& msg);
};

class FileOpenException : public std::runtime_error {
public:
    explicit FileOpenException(const std::string& msg);
};

enum class DataType {
    U16,
    U32,
    U64
};

class BinaryInspector {
private:
    std::string filename;
    std::size_t fileSize;

    void determineFileSize();

public:
    explicit BinaryInspector(const std::string& path);
    
    void printFileSize() const;
    void printHexAndAsciiDump(std::size_t limit = 64) const;
    void printByteFrequencies() const;
    void printValueAt(std::size_t offset, DataType type) const;
};

#endif
